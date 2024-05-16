#include "includes/linked_list_utils.h"

void	free_all(t_command_line **command_line)
{
	if (*command_line)
	{
		if ((*command_line)->substrings)
			free_substring(&(*command_line)->substrings);
		free_command_line(command_line);
	}
}

void	free_command_line(t_command_line **command_line)
{
	if (*command_line)
		free(*command_line);
}

void	free_substring(t_substring **substrings)
{
	t_substring	*tmp;

	while (ft_lst_size1(*substrings))
	{
		tmp = (*substrings)->next;
		if ((*substrings)->n_redirections)
			free_n_redirection(&(*substrings)->n_redirections);
		if ((*substrings)->n_arguments)
			free_n_argument(&(*substrings)->n_arguments);	
		free ((*substrings)->remaining_line);
		free ((*substrings)->n_redirections);
		free ((*substrings)->n_arguments);
		free ((*substrings));
		*substrings = tmp;
	}
}

void	free_n_redirection(t_native_redirection **n_redirections)
{
	t_native_redirection	*tmp;

	while (ft_lst_size2(*n_redirections))
	{
		tmp = (*n_redirections)->next;
		free ((*n_redirections)->content);
		free (*n_redirections);
		*n_redirections = tmp;
	}
}

void	free_n_argument(t_native_argument **n_arguments)
{
	t_native_argument	*tmp;

	while (ft_lst_size3(*n_arguments))
	{
		tmp = (*n_arguments)->next;
		free ((*n_arguments)->content);
		free (*n_arguments);
		*n_arguments = tmp;
	}
}
