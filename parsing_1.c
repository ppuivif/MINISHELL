#include "minishell.h"

t_command_line	*parse_command_line(char *str)
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
	ft_lst_print(command_line);
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
/*	if (str[0][0] == '<' && str[0][1] == '<' && str[0][2] == '<')
	{
		(*n_redirection).e_redirection = REDIRECTION_TEXT;
		*str += 3;
	}*/
	if (str[0][0] == '<' && str[0][1] == '<')
	{
		(*n_redirection).e_redirection = REDIRECTION_HEREDOC;
		*str += 2;
	}
	else if (str[0][0] == '>' && str[0][1] == '>')
	{
		(*n_redirection).e_redirection = REDIRECTION_APPEND;
		*str += 2;
	}
	else if (str[0][0] == '<')
	{
		(*n_redirection).e_redirection = REDIRECTION_INFILE;
		*str += 1;
	}
	else if (str[0][0] == '>')

	{
		(*n_redirection).e_redirection = REDIRECTION_OUTFILE;
		*str += 1;
	}
/*	else
	{
		(*n_redirection).e_redirection = REDIRECTION_INDEFINED;
		*str += 1;	
	}*/
}

int	get_redirections(char **remaining_line, t_substring *substring)
{
	size_t					len;
	t_native_redirection	*n_redirection;

	len = 0;
	n_redirection = NULL;
	if (init_redirection_struct(&n_redirection) == 1)
		return (1);
	get_redirection_type(remaining_line, n_redirection);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = strcspn(*remaining_line, " \n\t\0");
	if (strcspn(*remaining_line, "<>|") < len)
		return (2);
	else
	{
		n_redirection->content = ft_substr(*remaining_line, 0, len);
		*remaining_line += len;
		ft_lst_add_back2(&substring->n_redirections, n_redirection);
		return (0);
	}
}

int	get_arguments(char **remaining_line, t_substring *substring)
{
	int					len;
	t_native_argument	*n_argument;

	len = 0;
	n_argument = NULL;
	if (init_argument_struct(&n_argument) == 1)
		return (1);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (*remaining_line[0] == '\'')
	{
		len = check_quotes(*remaining_line, "\'");
		if (len == - 1)
			return (2);
	}
	else if (*remaining_line[0] == '\"')
	{
		len = check_quotes(*remaining_line, "\"");
		if (len == - 1)
			return (2);
	}
	else
	{
		len = (int)strcspn(*remaining_line, " \n\t\0");
		if ((int)strcspn(*remaining_line, "<>|") < len)
			return (3);
	}
	n_argument->content = ft_substr(*remaining_line, 0, len);
	*remaining_line += len;
	ft_lst_add_back3(&substring->n_arguments, n_argument);
	return (0);
}

int	check_quotes(char *remaining_line, char *c)
{
	int len;	

	len = 0;
	remaining_line++;
	len = strcspn(remaining_line, c);
	if (len == (int)ft_strlen(remaining_line))
		return (-1);
	return (len + 2);
}



/*size_t	check_quotes(char *remaining_line)
{
	size_t	len_single_quote;
	size_t	len_double_quote;
	
//	len_single_quote = count_quotes(remaining_line, '\'');
//	len_double_quote = count_quotes(remaining_line, '\"');
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
