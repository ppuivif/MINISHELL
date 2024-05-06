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
