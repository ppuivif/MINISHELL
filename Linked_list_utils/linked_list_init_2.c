/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_init_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/21 17:14:15 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"
#include "minishell.h"

int	init_native_argument_struct(t_native_argument **n_argument, \
t_command_line **command_line)
{
	*n_argument = ft_calloc(1, sizeof(t_native_argument));
	if (!*n_argument)
		error_allocation_command_line_and_exit(command_line);
	(*n_argument)->content = NULL;
	(*n_argument)->next = NULL;
	return (0);
}

int	init_native_redirection_struct(t_native_redirection **n_redirection, \
t_command_line **command_line)
{
	*n_redirection = ft_calloc(1, sizeof(t_native_redirection));
	if (!*n_redirection)
		error_allocation_command_line_and_exit(command_line);
	(*n_redirection)->content = NULL;
	(*n_redirection)->t_redirection = 4;
	(*n_redirection)->flag_for_expand = true;
	(*n_redirection)->next = NULL;
	return (0);
}

int	init_expanded_argument_struct(t_expanded_argument **exp_argument, \
t_command_line **command_line)
{
	*exp_argument = ft_calloc(1, sizeof(t_expanded_argument));
	if (!*exp_argument)
		error_allocation_command_line_and_exit(command_line);
	(*exp_argument)->alloc_succeed = true;//to delete
	(*exp_argument)->content = NULL;
	(*exp_argument)->next = NULL;
	return (0);
}

int	init_expanded_redirection_struct(t_expanded_redirection **exp_redirection, \
t_command_line **command_line)
{
	*exp_redirection = ft_calloc(1, sizeof(t_expanded_redirection));
	if (!*exp_redirection)
		error_allocation_command_line_and_exit(command_line);
	(*exp_redirection)->content = NULL;
	(*exp_redirection)->t_redirection = 4;
	(*exp_redirection)->flag_for_expand = true;
	(*exp_redirection)->next = NULL;
	return (0);
}
