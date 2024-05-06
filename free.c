#include "includes/linked_list_utils.h"

void	free_all(t_command_line **command_line)
{
	if (*command_line)
	{
		if ((*command_line)->substrings)
		{
			if ((*command_line)->substrings->n_redirections)
				free_n_redirection(&(*command_line)->substrings->n_redirections);
			if ((*command_line)->substrings->n_arguments)
				free_n_argument(&(*command_line)->substrings->n_arguments);
			free_substring(&(*command_line)->substrings);
		}
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
	t_substring	*element_to_free;

	while (*substrings)
	{
		element_to_free = ft_lst_last1(*substrings);
		free (element_to_free->remaining_line);
		free (element_to_free->n_redirections);
		free (element_to_free->n_arguments);
		free (element_to_free);
		element_to_free = NULL;
	}
}

void	free_n_redirection(t_native_redirection **redirections)
{
	t_native_redirection	*element_to_free;

	element_to_free = *redirections;
	while (*redirections && redirections)
	{
		free (element_to_free->content);
		free (element_to_free);
		element_to_free = NULL;
		
		printf("redirec\n");
	}

}

void	free_n_argument(t_native_argument **arguments)
{
	t_native_argument	*element_to_free;

	while (*arguments)
	{
		element_to_free = ft_lst_last3(*arguments);
		free (element_to_free->content);
		free (element_to_free);
	//	printf("arg\n");
		element_to_free = NULL;
	}
}