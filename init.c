/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/31 17:32:09 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/linked_list_utils.h"

int	init_envp_struct(t_envp_struct **envp_struct)
{
	*envp_struct = ft_calloc(1, sizeof(t_envp_struct));
	if (!*envp_struct)
		return (-1);
	(*envp_struct)->content = NULL;
	(*envp_struct)->next = NULL;
	return (0);
}

int	init_expanded_argument_struct(t_expanded_argument **exp_argument)
{
	*exp_argument = ft_calloc(1, sizeof(t_expanded_argument));
	if (!*exp_argument)
		return (-1);
	(*exp_argument)->alloc_succeed = true;
	(*exp_argument)->content = NULL;
	(*exp_argument)->next = NULL;
	return (0);
}

int	init_expanded_redirection_struct(t_expanded_redirection **exp_redirection)
{
	*exp_redirection = ft_calloc(1, sizeof(t_expanded_redirection));
	if (!*exp_redirection)
		return (-1);
	(*exp_redirection)->alloc_succeed = true;
	(*exp_redirection)->content = NULL;
	(*exp_redirection)->e_redirection = 4;
	(*exp_redirection)->next = NULL;
	return (0);
}

int	init_native_argument_struct(t_native_argument **n_argument)
{
	*n_argument = ft_calloc(1, sizeof(t_native_argument));
	if (!*n_argument)
		return (-1);
	(*n_argument)->content = NULL;
	(*n_argument)->next = NULL;
	return (0);
}

int	init_native_redirection_struct(t_native_redirection **n_redirection)
{
	*n_redirection = ft_calloc(1, sizeof(t_native_redirection));
	if (!*n_redirection)
		return (-1);
	(*n_redirection)->content = NULL;
	(*n_redirection)->e_redirection = 4;
	(*n_redirection)->next = NULL;
	return (0);
}

int	init_substring_struct(t_substring **substring)
{
	*substring = ft_calloc(1, sizeof(t_substring));
	if (!*substring)
		return (-1);	
	(*substring)->remaining_line = NULL;
	(*substring)->n_redirections = NULL;
	(*substring)->n_arguments = NULL;
	(*substring)->exp_redirections = NULL;
	(*substring)->exp_arguments = NULL;
	(*substring)->next = NULL;
	return (0);
}

int	init_command_line_struct(t_command_line **command_line)
{
	*command_line = ft_calloc(1, sizeof(t_command_line));
	if (!*command_line)
		return (-1);
	(*command_line)->exit_code = 0;
	(*command_line)->substrings = NULL;
	return (0);
}





int	init_redirection(t_redirection **redirection)
{
	*redirection = ft_calloc(1, sizeof(t_redirection));
	if (!*redirection)
		return (-1);	
	(*redirection)->file = NULL;
	(*redirection)->e_redirection = 4;
	(*redirection)->fd_input = -1;
	(*redirection)->fd_output = -1;
	(*redirection)->next = NULL;
	return (0);
}

int	init_execution_struct(t_execution **execution)
{
	*execution = ft_calloc(1, sizeof(t_execution));
	if (!*execution)
		return (-1);	
	(*execution)->redirections = NULL;
	(*execution)->commands = NULL;
	(*execution)->next = NULL;
	return (0);
}

int	init_main_struct(t_main_struct **main_struct)
{
	*main_struct = ft_calloc(1, sizeof(t_main_struct));
	if (!*main_struct)
		return (-1);
	(*main_struct)->exit_code = 0;
	(*main_struct)->executions = 0;
	return (0);
}
