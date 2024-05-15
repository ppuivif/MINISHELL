/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:36 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/15 11:05:13 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/linked_list_utils.h"
#include "includes/linked_list_utils.h"

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

void	ft_lst_add_back3(t_native_argument **head, t_native_argument *new_element)
{
	t_native_argument	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last3(*head);
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

t_native_argument	*ft_lst_last3(t_native_argument *head)
{
	t_native_argument	*last_element;

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

void	ft_lst_print(t_command_line *command_line, int fd)
{
	size_t	i;
	size_t	j;
	t_substring	*tmp1;
	t_native_redirection *tmp2;
	t_native_argument *tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->n_redirections;
		while (tmp1->n_redirections && j < ft_lst_size2(tmp1->n_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_e_redirection (tmp2->e_redirection, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->n_arguments;
		while (tmp1->n_arguments && j < ft_lst_size3(tmp1->n_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	print_e_redirection (int e_redirection, int fd)
{
	if (e_redirection == 0)
		ft_putstr_fd("REDIRECTION_OUTFILE", fd);
	if (e_redirection == 1)
		ft_putstr_fd("REDIRECTION_INFILE", fd);
	if (e_redirection == 2)
		ft_putstr_fd("REDIRECTION_INDEFINED", fd);
	if (e_redirection == 3)
		ft_putstr_fd("REDIRECTION_APPEND", fd);
	if (e_redirection == 4)
		ft_putstr_fd("REDIRECTION_HEREDOC", fd);
	if (e_redirection == 5)
		ft_putstr_fd("REDIRECTION_TEXT", fd);
	}

size_t	ft_lst_size1(t_substring *head)
{
	size_t		len;
	t_substring	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last1(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size2(t_native_redirection *head)
{
	size_t		len;
	t_native_redirection	*last_element;

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

size_t	ft_lst_size3(t_native_argument *head)
{
	size_t		len;
	t_native_argument	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last3(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}
