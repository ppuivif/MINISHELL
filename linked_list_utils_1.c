/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:36 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/31 18:04:41 by ppuivif          ###   ########.fr       */
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

void	ft_lst_add_back4(t_expanded_redirection **head, t_expanded_redirection *new_element)
{
	t_expanded_redirection	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last4(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
}

void	ft_lst_add_back5(t_expanded_argument **head, t_expanded_argument *new_element)
{
	t_expanded_argument	*last_element;

	if (!head || !new_element)
		return ;
	if (!*head)
	{
		*head = new_element;
		return ;
	}
	else
	{
		last_element = ft_lst_last5(*head);
		new_element->next = NULL;
		last_element->next = new_element;
	}
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

t_expanded_redirection	*ft_lst_last4(t_expanded_redirection *head)
{
	t_expanded_redirection	*last_element;

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

t_expanded_argument	*ft_lst_last5(t_expanded_argument *head)
{
	t_expanded_argument	*last_element;

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

t_envp_struct	*ft_lst_last6(t_envp_struct *head)
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

t_execution	*ft_lst_last7(t_execution *head)
{
	t_execution	*last_element;

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

t_redirection	*ft_lst_last8(t_redirection *head)
{
	t_redirection	*last_element;

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

t_command	*ft_lst_last9(t_command *head)
{
	t_command	*last_element;

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

void	ft_envp_struct_lst_print(t_envp_struct *envp_struct, int fd)
{
	size_t	i;
	t_envp_struct	*tmp;

	i = 0;
	tmp = envp_struct;
	while (tmp && i < ft_lst_size6(envp_struct))
	{
		ft_putstr_fd("envp[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("] : ", fd);
		ft_putstr_fd(tmp->content, fd);
//		ft_putstr_fd(envp_struct->content, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
//		envp_struct = envp_struct->next;
		i++;
	}
}

void	ft_native_lst_print(t_command_line *command_line, int fd)
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

void	ft_expanded_lst_print(t_command_line *command_line, int fd)
{
	size_t	i;
	size_t	j;
	t_substring	*tmp1;
	t_expanded_redirection *tmp2;
	t_expanded_argument *tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exp_redirections;
		while (tmp1->exp_redirections && j < ft_lst_size4(tmp1->exp_redirections))
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
		tmp3 = tmp1->exp_arguments;
		while (tmp1->exp_arguments && j < ft_lst_size5(tmp1->exp_arguments))
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

size_t	ft_lst_size4(t_expanded_redirection *head)
{
	size_t		len;
	t_expanded_redirection	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last4(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size5(t_expanded_argument *head)
{
	size_t		len;
	t_expanded_argument	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last5(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}


size_t	ft_lst_size6(t_envp_struct *head)
{
	size_t		len;
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

size_t	ft_lst_size7(t_execution *head)
{
	size_t		len;
	t_execution	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last7(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size8(t_redirection *head)
{
	size_t		len;
	t_redirection	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last8(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

size_t	ft_lst_size9(t_command *head)
{
	size_t		len;
	t_command	*last_element;

	len = 1;
	if (!head)
		return (0);
	last_element = ft_lst_last9(head);
	if (last_element == head)
		return (1);
	while (head != last_element)
	{
		head = head->next;
		len++;
	}
	return (len);
}

