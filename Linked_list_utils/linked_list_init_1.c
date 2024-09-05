/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_init_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/05 11:15:44 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_envp_struct(t_envp_struct **envp_struct)
{
	*envp_struct = ft_calloc(1, sizeof(t_envp_struct));
	if (!*envp_struct)
		error_allocation_envp_struct_and_exit(envp_struct);
	(*envp_struct)->name = NULL;
	(*envp_struct)->equal = 0;
	(*envp_struct)->value = NULL;
	(*envp_struct)->next = NULL;
	return (0);
}

int	init_command_line_struct(t_command_line **command_line)
{
	*command_line = ft_calloc(1, sizeof(t_command_line));
	if (!*command_line)
		error_allocation_command_line_and_exit(command_line);
	(*command_line)->previous_exit_code = 0;
	(*command_line)->current_exit_code = 0;
	(*command_line)->substrings = NULL;
	(*command_line)->envp_struct = NULL;
	return (0);
}

int	init_substring_struct(t_substring **substring, \
t_command_line **command_line)
{
	*substring = ft_calloc(1, sizeof(t_substring));
	if (!*substring)
		error_allocation_command_line_and_exit(command_line);
	(*substring)->substring_index = 0;
	(*substring)->remaining_line = NULL;
	(*substring)->n_redirections = NULL;
	(*substring)->n_arguments = NULL;
	(*substring)->exp_redirections = NULL;
	(*substring)->exp_arguments = NULL;
	(*substring)->next = NULL;
	return (0);
}
