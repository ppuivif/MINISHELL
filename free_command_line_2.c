/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_line_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:20 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/19 17:10:00 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"

static void	free_n_redirection(t_nativt_redirection **n_redirections)
{
	t_nativt_redirection	*tmp;

	while (ft_lst_size2(*n_redirections))
	{
		tmp = (*n_redirections)->next;
		(*n_redirections)->content = free_and_null((*n_redirections)->content);
		free(*n_redirections);
		*n_redirections = tmp;
	}
}

static void	free_n_argument(t_native_argument **n_arguments)
{
	t_native_argument	*tmp;

	while (ft_lst_size3(*n_arguments))
	{
		tmp = (*n_arguments)->next;
		(*n_arguments)->content = free_and_null((*n_arguments)->content);
		free(*n_arguments);
		*n_arguments = tmp;
	}
}

static void	free_exp_redirection(t_expanded_redirection **exp_redirections)
{
	t_expanded_redirection	*tmp;

	while (ft_lst_size4(*exp_redirections))
	{
		tmp = (*exp_redirections)->next;
		(*exp_redirections)->content = free_and_null((*exp_redirections)->content);
		free(*exp_redirections);
		*exp_redirections = tmp;
	}
}

static void	free_exp_argument(t_expanded_argument **exp_arguments)
{
	t_expanded_argument	*tmp;

	while (ft_lst_size5(*exp_arguments))
	{
		tmp = (*exp_arguments)->next;
		(*exp_arguments)->content = free_and_null((*exp_arguments)->content);
		free(*exp_arguments);
		*exp_arguments = tmp;
	}
}

void	free_substring(t_substring **substrings)
{
	t_substring	*tmp;

	while (ft_lst_size1(*substrings))
	{
		tmp = (*substrings)->next;
		if ((*substrings)->n_redirections)
		{
			free_n_redirection(&(*substrings)->n_redirections);
			free_exp_redirection(&(*substrings)->exp_redirections);
		}
		if ((*substrings)->n_arguments)
		{
			free_n_argument(&(*substrings)->n_arguments);
			free_exp_argument(&(*substrings)->exp_arguments);
		}
		(*substrings)->remaining_line = free_and_null((*substrings)->remaining_line);
		(*substrings)->n_redirections = free_and_null((*substrings)->n_redirections);
		(*substrings)->n_arguments = free_and_null((*substrings)->n_arguments);
		(*substrings)->exp_redirections = free_and_null((*substrings)->exp_redirections);
		(*substrings)->exp_arguments = free_and_null((*substrings)->exp_arguments);
		free((*substrings));
		*substrings = tmp;
	}
}
