#include "minishell.h"

t_command_line	*parse_command_line(char *str, t_envp_struct **envp_struct, int fd)//int fd is used only for script.sh execution
{
	t_command_line	*command_line;
	char			*remaining_line;

	command_line = NULL;
	if (init_command_line_struct(&command_line) == -1)
		error_allocation_command_line(&command_line, envp_struct);
	remaining_line = skip_first_whitespaces(str);
	if (ft_strlen(remaining_line) == 0)
		return (command_line);
	cut_remaining_line_on_pipes(&command_line, remaining_line, envp_struct);
	if (command_line->exit_code != 0)
		return (command_line);
	expand_contents(&command_line);
	ft_expanded_lst_print(command_line, fd);//to delete
//	ft_native_lst_print(command_line, fd);
	return (command_line);
}

void	cut_remaining_line_on_pipes(t_command_line **command_line, char *remaining_line, t_envp_struct **envp_struct)
{
	while(ft_strlen(remaining_line))
	{
		(*command_line)->exit_code = parse_substrings(&remaining_line, *command_line);
		if ((*command_line)->exit_code == -1)
			error_allocation_command_line(command_line, envp_struct);
		if ((*command_line)->exit_code != 0)//handle return of parse_substrings (1 or 2 when errors)
			return ;
		remaining_line = skip_first_whitespaces(remaining_line);
		if (remaining_line[0] == '|')
		{
			remaining_line++;
			remaining_line = skip_first_whitespaces(remaining_line);
			if (ft_strlen(remaining_line) == 0)
			{
				(*command_line)->exit_code = 2;//case of | at last position
				return ;
			}	
		}
	}
}

int	parse_substrings(char **remaining_line, t_command_line *command_line)
{
	t_substring		*substring;
	int return_value;	

	substring = NULL;
	return_value = 0;
	if (init_substring_struct(&substring) == -1)
		return (-1);
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (!*remaining_line || *remaining_line[0] == '|')//case of | at first position (to handle here or later when argument empty)
	{
		free(substring);
		return (2);// to confirm
	}
	if (ft_strlen(*remaining_line) == 0)
	{
		free(substring);
		return (0);// to confirm
	}
	return_value = get_arguments_and_redirections(&substring, remaining_line);
	if (return_value != 0)
	{
		free(substring);
		return (return_value);
	}
	ft_lst_add_back1(&command_line->substrings, substring);
	return (0);
}

int	get_arguments_and_redirections(t_substring **substring, char **remaining_line)
{
	int	return_value_redirections;
	int	return_value_arguments;
	
	return_value_redirections = 0;
	return_value_arguments = 0;
	while (*remaining_line[0] && *remaining_line[0] != '|')
	{
		if (*remaining_line[0] == '<' || *remaining_line[0] == '>')
		{
			return_value_redirections = get_redirections(remaining_line, *substring);
			if (return_value_redirections)
				return (return_value_redirections);
		}
		else
		{
			return_value_arguments =  get_arguments(remaining_line, *substring);
			if (return_value_arguments)
				return (return_value_arguments);
		}
		*remaining_line = skip_first_whitespaces(*remaining_line);
	}
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
	{
		free(n_redirection);
		return(2);
	}
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = count_len_to_cut(*remaining_line);
	if (len == -1)
	{
		free(n_redirection);
		return (2);
	}
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
	{
		free(n_argument);
		return (2);
	}
	n_argument->content = ft_substr(*remaining_line, 0, len);
	*remaining_line += len;
	ft_lst_add_back3(&substring->n_arguments, n_argument);
	return (0);
}

int	count_len_to_cut(char *remaining_line)
{
	int	len_to_quote;
	int	len;

	len_to_quote = 0;
	len = 0;
	if (remaining_line[0] == '\'')
		len_to_quote = count_len_to_next_quotes(remaining_line, "\'", 0);
	else if (remaining_line[0] == '\"')
		len_to_quote = count_len_to_next_quotes(remaining_line, "\"", 0);
	else
		len = count_len_to_reach_first_quote_or_ifs(remaining_line);
	if (len_to_quote == - 1 || len == -1)
		return (-1);
	len += len_to_quote;
	return (len);
}

int	count_len_to_reach_first_quote_or_ifs(char *remaining_line)
{
	int	len;
	int	len_to_ifs;
	int	len_to_quote;

	if (ft_strlen(skip_first_whitespaces(remaining_line)) == 0)
		return (-1);
	len = (int)strcspn(remaining_line, "\'\"");
	len_to_ifs = (int)strcspn(remaining_line, "<>| \t\n\v\f\r\0");
	len_to_quote = 0;
	if (len < len_to_ifs)
	{
		while (remaining_line[0] && remaining_line[0] != '\'' && \
		remaining_line[0] != '\"')
			remaining_line++;
		if (remaining_line[0] == '\'')
			len_to_quote = count_len_to_next_quotes(remaining_line, "\'", 0);
		if (remaining_line[0] == '\"')
			len_to_quote = count_len_to_next_quotes(remaining_line, "\"", 0);
		if (len_to_quote == -1)
			return (-1);
		len += len_to_quote;
	}
	else
		len = len_to_ifs;
	return (len);
}


int	count_len_to_next_quotes(char *remaining_line, char *c, int flag)
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
		if (((len_to_quote + flag + j) <= (len_to_end + 1)) && \
		(remaining_line[len_to_quote + flag + j] == '\''))
			return_value = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\'", 0);
		else if ((len_to_quote + flag + j) <= (len_to_end + 1) && \
		remaining_line[len_to_quote + flag + j] == '\"')
			return_value = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\"", 0);
		if ( return_value == -1)
				return (-1);
		len_to_quote += return_value;
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
