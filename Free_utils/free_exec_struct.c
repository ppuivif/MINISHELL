/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:27 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 11:16:03 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_exec_argument_struct(t_exec_argument **exec_arguments)
{
	t_exec_argument	*tmp;

	while (ft_lst_size9(*exec_arguments))
	{
		tmp = (*exec_arguments)->next;
		free(*exec_arguments);
		*exec_arguments = tmp;
	}
}

static void	free_exec_redirection_struct(t_exec_redirection **exec_redirections)
{
	t_exec_redirection	*tmp;

	while (ft_lst_size8(*exec_redirections))
	{
		tmp = (*exec_redirections)->next;
		close_fd((*exec_redirections)->fd_input);
		close_fd((*exec_redirections)->fd_output);
		(*exec_redirections)->file = free_and_null((*exec_redirections)->file);
		free(*exec_redirections);
		*exec_redirections = tmp;
	}
}

static void	free_exec_substring_struct(t_exec_substring **exec_substrings)
{
	t_exec_substring	*tmp;

	while (ft_lst_size7(*exec_substrings))
	{
		tmp = (*exec_substrings)->next;
		if ((*exec_substrings)->exec_redirections)
			free_exec_redirection_struct \
			(&(*exec_substrings)->exec_redirections);
		if ((*exec_substrings)->exec_arguments)
			free_exec_argument_struct(&(*exec_substrings)->exec_arguments);
		(*exec_substrings)->exec_redirections = free_and_null \
		((*exec_substrings)->exec_redirections);
		(*exec_substrings)->exec_arguments = free_and_null \
		((*exec_substrings)->exec_arguments);
		(*exec_substrings)->cmd_arr = free_and_null \
		((*exec_substrings)->cmd_arr);
		(*exec_substrings)->path_with_cmd = free_and_null \
		((*exec_substrings)->path_with_cmd);
		((*exec_substrings)->pid_arr) = free_and_null \
			((*exec_substrings)->pid_arr);
		free((*exec_substrings));
		*exec_substrings = tmp;
	}
}

void	free_all_exec_struct(t_exec_struct **exec_struct)
{
	if (*exec_struct)
	{
		if ((*exec_struct)->exec_substrings)
			free_exec_substring_struct(&(*exec_struct)->exec_substrings);
		*exec_struct = free_and_null(*exec_struct);
	}
}
