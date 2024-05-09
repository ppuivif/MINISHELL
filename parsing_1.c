#include "minishell.h"

t_command_line	*parse_command_line(char *str, int fd)
{
	t_command_line	*command_line;
	char			*remaining_line;
	int				return_value;

	command_line = NULL;
	return_value = 0;
	if (init_command_line_struct(&command_line) == 1)
		error_allocation(&command_line);
	remaining_line = skip_first_whitespaces(str);
	if (ft_strlen(remaining_line) == 0)
	{
		command_line->flag = false;
		return (command_line);
	}
	while(ft_strlen(remaining_line))
	{
		return_value = parse_substrings(&remaining_line, command_line);
		if (return_value == 1)
			error_allocation(&command_line);
		if (return_value == 2)
		{
			command_line->flag = false;
			return (command_line);
		}
		remaining_line = skip_first_whitespaces(remaining_line);
		if (remaining_line[0] == '|')
		{
			remaining_line++;
			remaining_line = skip_first_whitespaces(remaining_line);
			if (ft_strlen(remaining_line) == 0)
			{
				command_line->flag = false;
				return (command_line);
			}	
		}
	}
	ft_lst_print(command_line, fd);
	return (command_line);
}

int	parse_substrings(char **remaining_line, t_command_line *command_line)
{
	t_substring		*substring;
	int				return_value_redirections;
	int				return_value_arguments;

	substring = NULL;
	return_value_redirections = 0;
	return_value_arguments = 0;
	if (init_substring_struct(&substring) == 1)
		return (1);
	if (!*remaining_line)
		return (2);//to confirm
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (ft_strlen(*remaining_line) == 0)
		return (2);// to confirm
	while (*remaining_line[0] && *remaining_line[0] != '|')
	{
		if (*remaining_line[0] == '<' || *remaining_line[0] == '>')
		{
			return_value_redirections = get_redirections(remaining_line, substring);
			if (return_value_redirections)
				return (return_value_redirections);
		}
		else
		{
			return_value_arguments =  get_arguments(remaining_line, substring);
			if (return_value_arguments)
				return (return_value_arguments);
		}
		*remaining_line = skip_first_whitespaces(*remaining_line);
	}
	ft_lst_add_back1(&command_line->substrings, substring);
	return (0);
}


static void get_redirection_type(char **str, t_native_redirection *n_redirection)
{
	if (count_angled_bracket(*str) > 2)
		(*n_redirection).e_redirection = REDIRECTION_INDEFINED;
	else if (count_angled_bracket(*str) == 2)
	{
		if (str[0][0] == '<' && str[0][1] == '<')
			(*n_redirection).e_redirection = REDIRECTION_HEREDOC;
		else if (str[0][0] == '>' && str[0][1] == '>')
			(*n_redirection).e_redirection = REDIRECTION_APPEND;
		else
			(*n_redirection).e_redirection = REDIRECTION_INDEFINED;
		*str += 2;
	}
	else
	{
		if (str[0][0] == '<')
			(*n_redirection).e_redirection = REDIRECTION_INFILE;
		else if (str[0][0] == '>')
			(*n_redirection).e_redirection = REDIRECTION_OUTFILE;
		else
			(*n_redirection).e_redirection = REDIRECTION_INDEFINED;
		*str += 1;
	}
}

int		get_redirections(char **remaining_line, t_substring *substring)
{
	unsigned int			len;
	t_native_redirection	*n_redirection;

	len = 0;
	n_redirection = NULL;
	if (init_redirection_struct(&n_redirection) == 1)
		return (1);
	get_redirection_type(remaining_line, n_redirection);
	if (n_redirection->e_redirection == -1)
		return(2);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = strcspn(*remaining_line, "<>| \t\n\v\f\r\0");
	n_redirection->content = ft_substr(*remaining_line, 0, len);
	*remaining_line += len;
	ft_lst_add_back2(&substring->n_redirections, n_redirection);
	return (0);
}

int	get_arguments(char **remaining_line, t_substring *substring)
{
	int					len;
	int					len_quote;
	t_native_argument	*n_argument;

	len = 0;
	len_quote = 0;
	n_argument = NULL;
	if (init_argument_struct(&n_argument) == 1)
		return (1);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (*remaining_line[0] == '\'')
		len_quote = check_quotes(*remaining_line, '\'', 0);
	else if (*remaining_line[0] == '\"')
		len_quote = check_quotes(*remaining_line, '\"', 0);
/*	else
		len_quote = strcspn(*remaining_line, "\'\"");
		len_ifs = (int)strcspn(*remaining_line, "<>| \t\n\v\f\r\0");
		if (len_quote < len_ifs)
			fonction_en_francais;
		else
			len = len_ifs;*/
	if (len_quote == - 1)
	{
		printf("here\n");
		return (2);
	}
	n_argument->content = ft_substr(*remaining_line, 0, len + len_quote);
	*remaining_line += len + len_quote;
	ft_lst_add_back3(&substring->n_arguments, n_argument);
	return (0);
}

int	check_quotes(char *remaining_line, char c, int len)
{
	int j;

//	j = 1;
	j = 0;
	remaining_line++;
//	len = (int)strcspn(&remaining_line[j], &c);
	len = (int)strcspn(&remaining_line[0], &c);
//	if (len == (int)ft_strlen(&remaining_line[j]))
	if (len == (int)ft_strlen(&remaining_line[0]))
		return (-1);
	while (remaining_line[len + 1 + j] &&
		(remaining_line[len + 1 + j] != '<' || remaining_line[len + 1 + j] != '>' ||
		remaining_line[len + 1 + j] != '|' || isspace(remaining_line[len + 1 + j]) != 0))
	{
		if (remaining_line[len + 1 + j] == '\'')
		{
			len += check_quotes(&remaining_line[len + 1 + j], '\'', len) + 2;
			if (len == 1)
				return (-1);
		}
		if (remaining_line[len + 1 + j] == '\"')
		{
			len = check_quotes(&remaining_line[len + 1 + j], '\"', len);   			
			if (len == -1)
				return (-1);
			len += 2;
		}
		if (strcspn(&remaining_line[len + 1 + j], "\'\"") == ft_strlen(&remaining_line[len + 1 + j]))
			len++;
		j++;
	}
	return (len + 3);
}
 
unsigned int count_angled_bracket(char *str)
{
	unsigned int nmemb;

	nmemb = 0; 
	while(str && (*str == '<' || *str == '>' || ft_isspace(*str) == 0))
	{
		if (*str == '<' || *str == '>')
		nmemb++;
		str++;
	}
	return (nmemb);
}



/*size_t	ch	if (str[0][0] == '<' && str[0][1] != '<' && str[0][1] != '>')
e_quote = count_quotes(remaining_line, '\"');
	if (len_single_quote)
		return (len_single_quote);
	return (0);
}

size_t	count_quotes(char *remaining_line, size_t len, char quote)
{
	int				flag;

	flag = 0;
	while (remaining_line[0] && len && remaining_line[0] == quote)
	{
		if (remaining_line[0] == quote)
			flag++;
		remaining_line++;
		len--;
	}
	while (remaining_line[0] && len && remaining_line[0] != quote)
	{
		remaining_line++;
		len--;
	}
	while (remaining_line[0] && len && remaining_line[0] == quote)
	{
		if (remaining_line[0] == quote)
			flag--;
		remaining_line++;
		len--;
	}
	if (flag)
		return (2);
	return (0);
}*/
