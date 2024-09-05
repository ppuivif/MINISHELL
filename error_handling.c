/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 17:58:49 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_allocation_envp_struct_and_exit(t_envp_struct **envp_struct)
{
	ft_putstr_fd("error : an allocation failed\n", 2);
	free_envp_struct(envp_struct);
	exit(EXIT_FAILURE);
}

void	error_allocation_exec_struct_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	error_allocation_command_line_and_exit(&(*exec_struct)->command_line);
}

void	error_allocation_command_line_and_exit(t_command_line **command_line)
{
	ft_putstr_fd("error : an allocation failed\n", 2);
	free_envp_struct(&(*command_line)->envp_struct);
	free_all_command_line(command_line);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	error_pipe_creation_and_exit(t_exec_struct **exec_struct)
{
	ft_putstr_fd("error : a pipe creation failed\n", 2);
	free_all_exec_struct(exec_struct);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	rl_clear_history();
	exit(EXIT_FAILURE);
}

void	error_fork_creation_and_exit(t_exec_struct **exec_struct)
{
	ft_putstr_fd("error : a fork creation failed\n", 2);
	free_all_exec_struct(exec_struct);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	rl_clear_history();
	exit(EXIT_FAILURE);
}
