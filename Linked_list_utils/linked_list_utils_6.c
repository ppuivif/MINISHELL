/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:36 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 16:04:28 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"

static t_envp_struct	*ft_lst_last6(t_envp_struct *head)
{
	t_envp_struct	*last_element;

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

void	ft_lst_add_back6(t_envp_struct **head, t_envp_struct *new_element)
{
	t_envp_struct	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last6(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
}

size_t	ft_lst_size6(t_envp_struct *head)
{
	size_t			len;
	t_envp_struct	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last6(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}
