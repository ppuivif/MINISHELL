#include "minishell.h"

/*t_element parse_command_line(char *str)
{
	t_element	command_line;
	char		*remaining_line;	
	
	init_element_struct(&command_line);
	if (!str)
		return (command_line);
	remaining_line = skip_first_spaces(str);
	if (ft_strlen(remaining_line) == 0)
		return (command_line);
	parse_between_pipes(remaining_line);
	command_line.line = remaining_line;	
//	printf("%s\n", command_line.line);
	return (command_line);
}

t_element parse_between_pipes(char *str)
{
	t_element	command;
	char		*remaining_line;	

	init_element_struct(&command);
	if (!str)
		return (command);
	remaining_line = skip_first_spaces(str);
	if (ft_strlen(remaining_line) == 0)
		return (command);
	command.line = extract_substring(remaining_line, '|');
	printf ("substring : %s\n", command.line);
	free(command.line);
	remaining_line = ft_strdup(ft_strchr(remaining_line, '|'));
	printf ("remaining_line : %s\n", remaining_line);
	free(remaining_line);
	return (command);
}*/


t_command_line	parse_command_line(char *str)
{
	t_command_line	command_line;
	char			*remaining_line;

	init_command_line_struct(&command_line);
	if (!str)
	{
		command_line.flag = false;
		return (command_line);
	}
	remaining_line = skip_first_spaces(str);
	if (ft_strlen(remaining_line) == 0)
	{
		command_line.flag = false;
		return (command_line);
	}
	command_line = parse_substrings(remaining_line);
/*	while(ft_strlen(remaining_line))
	{
		command_line = parse_command(&remaining_line);
		remaining_line++;
	}*/
	return (command_line);


}

t_command_line	parse_substrings(char *str)
{
	t_command_line	command_line;
	t_substring		substring;
	char			*remaining_line;

	init_command_line_struct(&command_line);
	init_substring_struct(&substring);
	if (!str)
	{
		command_line.flag = false;
		return (command_line);
	}
	remaining_line = skip_first_spaces(str);
	if (ft_strlen(remaining_line) == 0)
	{
		command_line.flag = false;
		return (command_line);
	}
	while (remaining_line[0] && remaining_line[0] != '|')
	{
		if (remaining_line[0] == '<' || remaining_line[0] == '>')
		{
			get_redirections(remaining_line, &substring);
			remaining_line = substring.remaining_line;
	//		printf ("remaining_line : %s\n", substring.remaining_line);

		}
/*		else
		{
			remaining_line = skip_first_spaces(remaining_line);
			len = strcspn(remaining_line, " \n\t");
			printf ("len : %ld\n", len);
			tmp2 = ft_substr(remaining_line, 0, len);
			remaining_line += len;
			printf ("remaining_line : %s\n", remaining_line);
			printf ("argument : %s\n", tmp2);
		}*/
		//remaining_line = skip_first_spaces(remaining_line);
		remaining_line++;
	}
	ft_lst_add_back1(&command_line.substrings, &substring);
	/*printf ("remaining_line : %s\n", remaining_line);
	printf ("redirection 1 : %s\n", command_line.substrings->n_redirections->content);
	printf ("redirection 2 : %s\n", command_line.substrings->n_redirections->next->content);
	printf ("redirection 1 : %d\n", command_line.substrings->n_redirections->e_redirection);
	printf ("redirection 2 : %d\n", command_line.substrings->n_redirections->next->e_redirection);*/
	return (command_line);
}


static void get_redirection_type(char **str, t_native_redirection *n_redirection)
{
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

void	get_redirections(char *str, t_substring *substring)
{
	size_t					len;
	t_native_redirection	n_redirection;

	len = 0;
	init_redirection_struct(&n_redirection);
	get_redirection_type(&str, &n_redirection);
	(*substring).remaining_line = skip_first_spaces(str);
	len = strcspn((*substring).remaining_line, " \n\t");
	if (strcspn((*substring).remaining_line, "<>") < len)
		(*substring).flag = false;//to complete
	else
	{
		n_redirection.content = ft_substr((*substring).remaining_line, 0, len);
		(*substring).remaining_line += len;
		printf("len : %ld\n", len);
		ft_lst_add_back2(&(*substring).n_redirections, &n_redirection);
	}
	printf ("remaining_line : %s\n", (*substring).remaining_line);
	printf ("redirection 1 : %s\n", substring->n_redirections->content);
	//printf ("redirection 2 : %s\n", substring->n_redirections->next->content);
	printf ("redirection 1 : %d\n", substring->n_redirections->e_redirection);
	//printf ("redirection 2 : %d\n", substring->n_redirections->next->e_redirection);
	
}



/*t_substring get_arguments(char *remaining_line, t_substring substring)
{
	size_t		len;

	remaining_line++;
	remaining_line = skip_first_spaces(remaining_line);
	len = strcspn(remaining_line, " \n\t");
	printf ("len : %ld\n", len);
	substring.n_arguments->content = ft_substr(remaining_line, 0, len);
	remaining_line += len;
	printf ("remaining_line : %s\n", remaining_line);
	printf ("redirection : %s\n", tmp1)

}*/

