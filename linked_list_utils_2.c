/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:09:04 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/05 18:09:05 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/linked_list_utils.h"
#include "includes/linked_list_utils.h"


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

/*static int	ft_lst_delone_util(t_element **head, t_element *element_to_del)
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
}*/

