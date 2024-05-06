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
	remaining_line = skip_first_spaces(str);
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
		remaining_line = skip_first_spaces(remaining_line);
		if (remaining_line[0] == '|')
		{
			remaining_line++;
			remaining_line = skip_first_spaces(remaining_line);
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
	*remaining_line = skip_first_spaces(*remaining_line);
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
		*remaining_line = skip_first_spaces(*remaining_line);
	}
	ft_lst_add_back1(&command_line->substrings, substring);
	return (0);
}


static void get_redirection_type(char **str, t_native_redirection *n_redirection)
{
	if (str[0][0] == '<' && str[0][1] == '<' && str[0][2] == '<')
	{
		(*n_redirection).e_redirection = REDIRECTION_TEXT;
		*str += 3;
	}
	else if (str[0][0] == '<' && str[0][1] == '<')
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
	else
	{
		(*n_redirection).e_redirection = REDIRECTION_INDEFINED;
		*str += 1;	
	}
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
	*remaining_line = skip_first_spaces(*remaining_line);
	len = strcspn(*remaining_line, " \n\t\0");
	if (strcspn(*remaining_line, "<>|") < len)
//		n_redirection->e_redirection = 5;
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
	size_t				len;
	t_native_argument	*n_argument;

	len = 0;
	n_argument = NULL;
	if (init_argument_struct(&n_argument) == 1)
		return (1);
	*remaining_line = skip_first_spaces(*remaining_line);
	len = strcspn(*remaining_line, " \n\t\0");
	if (strcspn(*remaining_line, "<>|") < len)
		return (2);
	else
	{
		n_argument->content = ft_substr(*remaining_line, 0, len);
		*remaining_line += len;
		ft_lst_add_back3(&substring->n_arguments, n_argument);
		return (0);
	}
}

