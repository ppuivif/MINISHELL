#include "includes/linked_list_utils.h"

size_t	ft_lst_size(t_element *head)
{
	size_t		len;
	t_element	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

/*static void	free_build_list_element(t_element *element_to_del)
{
	if(element_to_del)
	{
		free_arr(element_to_del->arr);
		if (element_to_del->line)
			free(element_to_del->line);
		if (element_to_del->path)
			free(element_to_del->path);
		free(element_to_del);
	}
}*/

static int	ft_lst_delone_util(t_element **head, t_element *element_to_del)
{
	int	size;

	size = ft_lst_size(*head);
	if (size == 1)
	{
		*head = NULL;
//		free_build_list_element(element_to_del);
		return (1);
	}
	else if (size == 2)
	{
		*head = (*head)->next ;
		(*head)->next = NULL;
//		free_build_list_element(element_to_del);
		return (1);
	}
	*head = element_to_del->next;
	return (0);
}

void	ft_lst_delone(t_element **head, t_element *element_to_del)
{
	t_element	*element_to_search;

	if (!element_to_del || !head)
		return ;
	if (*head == element_to_del)
	{
		if (ft_lst_delone_util(head, element_to_del) == 1)
			return ;
	}
	element_to_search = *head;
	while (element_to_search->next != element_to_del)
		element_to_search = element_to_search->next;
	element_to_search->next = element_to_search->next->next;
//	free_build_list_element(element_to_del);
}

void	ft_lst_print(t_element *head)
{
	int	len;
	int	i;

	i = 0;
	len = ft_lst_size(head);
	while (i < len)
	{
		ft_putstr_fd("line ", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" : ", 1);
		ft_putstr_fd(head->line, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
		i++;
	}
}

/*void	ft_lst_dc_print(t_element *head)
{
	int	len;
	int	i;

	i = 0;
	len = ft_lst_dc_size(head);
	ft_putstr_fd("index\tcmd\t\toption1\t\toption2\t\tpath\n", 1);
	while (i < len)
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("\t", 1);
		ft_putstr_fd(head->arr[0], 1);
		ft_putstr_fd("\t\t", 1);
		ft_putstr_fd(head->arr[1], 1);
		ft_putstr_fd("\t\t", 1);
		ft_putstr_fd(head->arr[2], 1);
		ft_putstr_fd("\t\t", 1);
		ft_putstr_fd(head->path, 1);
		ft_putstr_fd("\n", 1);
		head = head->next;
		i++;
	}
	ft_putstr_fd("\n", 1);
}*/
