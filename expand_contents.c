/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_contents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:25 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/11 06:33:26 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_alloc_exp_arguments(t_expanded_argument *expand_arguments, t_command_line **command_line)
{
	t_expanded_argument	*cursor;

	cursor = expand_arguments;
	while (cursor)
	{
		if (cursor->alloc_succeed == false)
			error_allocation_command_line_and_exit(command_line);
		cursor = cursor->next;
	}
}

static void check_alloc_exp_redirections(t_expanded_redirection *expand_redirections, t_command_line **command_line)
{
	t_expanded_redirection	*cursor;

	cursor = expand_redirections;
	while (cursor)
	{
		if (cursor->alloc_succeed == false)
			error_allocation_command_line_and_exit(command_line);
		cursor = cursor->next;
	}
}

void	expand_contents(t_command_line **command_line)
{
	t_substring				*tmp1;
	t_native_redirection	*tmp2;
	t_native_argument		*tmp3;

	tmp1 = (*command_line)->substrings;
	while (tmp1)
	{
		tmp2 = tmp1->n_redirections;
//		while (tmp2 && (*command_line)->current_exit_code == 0)
		while (tmp2 && (*command_line)->current_exit_code != 2)
//		while (tmp2)
		{
			expand_redirections(tmp1, tmp2, command_line);
			if ((*command_line)->current_exit_code == 1)//ambiguous redirection
				break ;
			check_alloc_exp_redirections(tmp1->exp_redirections, command_line);
			tmp2 = tmp2->next;
		}
		tmp3 = tmp1->n_arguments;
//		while (tmp3 && (*command_line)->current_exit_code == 0)
		while (tmp3 && (*command_line)->current_exit_code != 2)
//		while (tmp3)
		{
			expand_arguments(tmp1, tmp3, command_line);
//			exit_code to check ?
			check_alloc_exp_arguments(tmp1->exp_arguments, command_line);
			tmp3 = tmp3->next;
		}
		tmp1 = tmp1->next;
	}
}
