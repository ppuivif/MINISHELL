#include "minishell.h"

t_command_line	*parse_command_line(char *str, int fd)
{
	t_command_line	*command_line;
	char			*remaining_line;

	command_line = NULL;
	if (init_command_line_struct(&command_line) == -1)
		error_allocation(&command_line);
	remaining_line = skip_first_whitespaces(str);
	if (ft_strlen(remaining_line) == 0)
		return (command_line);
	while(ft_strlen(remaining_line))
	{
		command_line->exit_code = parse_substrings(&remaining_line, command_line);
		if (command_line->exit_code == -1)
			error_allocation(&command_line);
		if (command_line->exit_code != 0)//handle return of parse_substrings (1 or 2 when errors)
			return (command_line);
		remaining_line = skip_first_whitespaces(remaining_line);
		if (remaining_line[0] == '|')
		{
			remaining_line++;
			remaining_line = skip_first_whitespaces(remaining_line);
			if (ft_strlen(remaining_line) == 0)
			{
				command_line->exit_code = 2;
				return (command_line);
			}	
		}
	}
	expand_contents(&command_line);
	ft_expanded_lst_print(command_line, fd);
//	ft_native_lst_print(command_line, fd);
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
	if (init_substring_struct(&substring) == -1)
		return (-1);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (!*remaining_line || *remaining_line[0] == '|')//case of | first to handle here or later when argument empty
	{
		command_line->exit_code = 2;
		return (2);// to confirm
	}
	if (ft_strlen(*remaining_line) == 0)
		return (1);// to confirm
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
	int						len;
	t_native_redirection	*n_redirection;

	len = 0;
	n_redirection = NULL;
	if (init_native_redirection_struct(&n_redirection) == -1)
		return (-1);
	get_redirection_type(remaining_line, n_redirection);
	if (n_redirection->e_redirection == 2)
		return(2);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = count_len_to_cut(*remaining_line);
	if (len == -1)
		return (2);
	n_redirection->content = ft_substr(*remaining_line, 0, len);
	*remaining_line += len;
	ft_lst_add_back2(&substring->n_redirections, n_redirection);
	return (0);
}

int	get_arguments(char **remaining_line, t_substring *substring)
{
	int					len;
	t_native_argument	*n_argument;

	len = 0;
	n_argument = NULL;
	if (init_native_argument_struct(&n_argument) == -1)
		return (-1);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = count_len_to_cut(*remaining_line);
	if (len == -1)
		return (2);
	n_argument->content = ft_substr(*remaining_line, 0, len);
	*remaining_line += len;
	ft_lst_add_back3(&substring->n_arguments, n_argument);
	return (0);
}

int	count_len_to_cut(char *remaining_line)
{
	int	i;
	int	len_to_quote;
	int	len_to_ifs;
	int	len;

	i = 0;
	len_to_quote = 0;
	len_to_ifs = 0;
	len = 0;
	if (remaining_line[0] == '\'' || remaining_line[0] == '\"')
		len_to_quote = \
	count_len_to_quotes(remaining_line, (char []){remaining_line[0], '\0'}, 0);
/*	if (remaining_line[0] == '\'')
		len_to_quote = count_len_to_quotes(remaining_line, "\'", 0);
	else if (remaining_line[0] == '\"')
		len_to_quote = count_len_to_quotes(remaining_line, "\"", 0);*/
	else
	{
		len = (int)strcspn(remaining_line, "\'\"");
		len_to_ifs = (int)strcspn(remaining_line, "<>| \t\n\v\f\r\0");
		if (ft_strlen(skip_first_whitespaces(remaining_line)) == 0)
			return (-1);
		if (len < len_to_ifs)
		{
			while (remaining_line[i] && remaining_line[i] != '\'' && \
			remaining_line[i] != '\"')
				i++;
			if (remaining_line[i] == '\'' || remaining_line[i] == '\"')
				len_to_quote = \
				count_len_to_quotes(&remaining_line[i], (char []){remaining_line[i], '\0'}, 0);			
/*			if (remaining_line[i] == '\'')
				len_to_quote = count_len_to_quotes(&remaining_line[i], "\'", 0);
			if (remaining_line[i] == '\"')
				len_to_quote = count_len_to_quotes(&remaining_line[i], "\"", 0);*/
			if (len_to_quote == -1)
				return (-1);
		}
		else
			len = len_to_ifs;
	}
	if (len_to_quote == - 1)
		return (-1);
	len += len_to_quote;
	return (len);
}



int	count_len_to_quotes(char *remaining_line, char *c, int flag)
{
	int j;
	int len_to_quote;
	int len_to_end;
	int	return_value;

	j = 1;
	flag += 1;
	len_to_quote = (int)strcspn(&remaining_line[1], c);
	len_to_end = (int)ft_strlen(&remaining_line[1]);
	return_value = 0;
	if (len_to_quote == len_to_end)
		return (-1);
	while (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
	{
		if (((len_to_quote + flag + j) <= (len_to_end + 1)) && ((remaining_line[len_to_quote + flag + j] == '\'') || \
		(remaining_line[len_to_quote + flag + j] == '\"')))
 		{
			return_value = \
			count_len_to_quotes(&remaining_line[len_to_quote + flag + j], (char []){remaining_line[len_to_quote + flag + j], '\0'}, 0);
/*		{
			return_value = count_len_to_quotes(&remaining_line[len_to_quote + flag + j], "\'", 0);
			if ( return_value == -1)
				return (-1);
			len_to_quote += return_value;
		}
		if ((len_to_quote + flag + j) <= (len_to_end + 1) && remaining_line[len_to_quote + flag + j] == '\"')
		{
			return_value = count_len_to_quotes(&remaining_line[len_to_quote + flag + j], "\"", 0);
			if ( return_value == -1)
				return (-1);
			len_to_quote += return_value;
		}*/
			if ( return_value == -1)
				return (-1);
			len_to_quote += return_value;
		}
		if (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
			j++;
	}
	return (len_to_quote + (flag + 1) + (j - 1));
}

int	check_char_validity(char *remaining_line, int len_to_quote, int flag, int j)
{
	int len_to_end;

	len_to_end = (int)ft_strlen(&remaining_line[1]);
	if (!remaining_line[len_to_quote + flag + j] || (len_to_quote + flag + j) > (len_to_end + 1))
		return (-1);
	if (remaining_line[len_to_quote + flag + j] == '>' || \
	remaining_line[len_to_quote + flag + j] == '|' || \
	ft_isspace(remaining_line[len_to_quote + flag + j]) == 0)
		return (-1);
	else
		return(0);
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
