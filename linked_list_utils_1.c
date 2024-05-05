//#include "includes/linked_list_utils.h"
#include "minishell.h"

/*int	init_list_struct(t_list	**list, int size)
{
	*list = malloc(sizeof(t_list));
	if (!list)
		return (1);
	(*list)->head = NULL;
	(*list)->size = size;
	return (0);
}

void	init_element_struct(t_element *element)
{
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!*cmd)
	{
		ft_putstr_fd("error\nstructure allocation failed\n", 2);
		exit (EXIT_FAILURE);
	}
	element->line = NULL;
	element->arr = NULL;
	element->path = NULL;
	element->next = NULL;
	element->previous = NULL;
}

t_element	*ft_lst_dc_new(char *line, char **arr, char *path)
{
	t_element	*new_element;

	new_element = malloc(sizeof(t_element));
	if (!new_element)
		return (NULL);
	else
	{
		new_element->line = line;
		new_element->arr = arr;
		new_element->path = path;
		new_element->next = NULL;
		new_element->previous = NULL;
	}
	return (new_element);
}*/

void	ft_lst_add_back(t_element **head, t_element *new_element)
{
	t_element	*last_element;

	if (!new_element || !head)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
}


void	ft_lst_add_front(t_element **head, t_element *new_element)
{
	if (!new_element || !head)
		return ;
	if (!*head)
		*head = new_element;
	else
	{
		new_element->next = *head;
		*head = new_element;
	}
}

t_element	*ft_lst_last(t_element *head)
{
	t_element	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}

void	ft_lst_add_back1(t_substring **head, t_substring *new_element)
{
	t_substring	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last1(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
}

t_substring	*ft_lst_last1(t_substring *head)
{
	t_substring	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}

void	ft_lst_add_back2(t_native_redirection **head, t_native_redirection *new_element)
{
	t_native_redirection	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last2(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
}

t_native_redirection	*ft_lst_last2(t_native_redirection *head)
{
	t_native_redirection	*last_element;

	if (!head)
		return (NULL);
	if (!head->next)
		last_element = head;
	else
	{
		last_element = head;
		while (last_element->next)
			last_element = last_element->next;
	}
	return (last_element);
}
