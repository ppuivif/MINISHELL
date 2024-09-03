/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_init_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/02 17:13:00 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"
#include "minishell.h"

int	init_exec_struct(t_exec_struct **exec_struct)
{
	*exec_struct = ft_calloc(1, sizeof(t_exec_struct));
	if (!*exec_struct)
		return (-1);
	(*exec_struct)->exit_code = 0;
	(*exec_struct)->exec_substrings = 0;
	(*exec_struct)->envp_struct = NULL;
	return (0);
}

int	init_exec_argument_struct(t_exec_argument **exec_argument, \
t_exec_struct **exec_struct)
{
	*exec_argument = ft_calloc(1, sizeof(t_exec_argument));
	if (!*exec_argument)
		error_allocation_exec_struct_and_exit(exec_struct);
	(*exec_argument)->argument = NULL;
	(*exec_argument)->is_argument_valid = true;
	(*exec_argument)->is_builtin = ISNOT_BUILTIN;
	(*exec_argument)->next = NULL;
	return (0);
}

int	init_exec_redirection_struct(t_exec_redirection **exec_redirection, \
t_exec_struct **exec_struct)
{
	*exec_redirection = ft_calloc(1, sizeof(t_exec_redirection));
	if (!*exec_redirection)
		error_allocation_exec_struct_and_exit(exec_struct);
	(*exec_redirection)->file = NULL;
	(*exec_redirection)->t_redirection = 2;
	(*exec_redirection)->fd_input = -2;
	(*exec_redirection)->fd_output = -2;
	(*exec_redirection)->next = NULL;
	return (0);
}

int	init_exec_substring_struct(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	*exec_substring = ft_calloc(1, sizeof(t_exec_substring));
	if (!*exec_substring)
		error_allocation_exec_struct_and_exit(exec_struct);
	(*exec_substring)->exec_redirections = NULL;
	(*exec_substring)->is_previous_file_opened = true;
	(*exec_substring)->exec_arguments = NULL;
	(*exec_substring)->cmd_arr = NULL;
	(*exec_substring)->path_with_cmd = NULL;
	(*exec_substring)->pid_arr = NULL;
	(*exec_substring)->fd_in = STDIN_FILENO;
	(*exec_substring)->fd_out = STDOUT_FILENO;
	(*exec_substring)->fd[0] = STDIN_FILENO;
	(*exec_substring)->fd[1] = STDOUT_FILENO;
	(*exec_substring)->next = NULL;
	return (0);
}
