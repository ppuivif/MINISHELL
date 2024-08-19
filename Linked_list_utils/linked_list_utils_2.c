/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:36 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 17:10:00 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"

static t_nativt_redirection	*ft_lst_last2(t_nativt_redirection *head)
{
	t_nativt_redirection	*last_element;

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

void	ft_lst_add_back2(t_nativt_redirection **head, t_nativt_redirection *new_element)
{
	t_nativt_redirection	*last_element;

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

size_t	ft_lst_size2(t_nativt_redirection *head)
{
	size_t					len;
	t_nativt_redirection	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last2(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}
