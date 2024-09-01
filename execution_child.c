/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/30 14:50:11 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_before_execve(t_exec_struct **exec_struct)
{
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	free_all_exec_struct(exec_struct);
}

static int	exit_code_and_fd_handle_in_child(t_exec_substring **substring, \
t_exec_struct **exec_struct)
{
	int	exit_code;

	exit_code = 0;
	if ((*substring)->exec_arguments && \
	(*substring)->exec_arguments->is_argument_valid == false)
		exit_code = (*exec_struct)->command_line->current_exit_code;
	if ((*substring)->fd_in == -1 || (*substring)->fd_out == -1)
		exit_code = 1;
	if ((*substring)->fd_in > 2)
	{
		dup2((*substring)->fd_in, STDIN_FILENO);
		close_fd((*substring)->fd_in);
	}
	if ((*substring)->fd_out > 2)
	{
		dup2((*substring)->fd_out, STDOUT_FILENO);
		close_fd((*substring)->fd_out);
	}
	close_fd((*substring)->fd[0]);
	close_fd((*substring)->fd[1]);
	return (exit_code);
}

static char	*copy_path(t_exec_substring *substring, \
t_exec_struct **exec_struct, char **cmd_arr, char **envp_arr)
{
	char	*path_with_cmd;

	path_with_cmd = NULL;
	if (substring->path_with_cmd)
	{
		path_with_cmd = ft_strdup(substring->path_with_cmd);
		if (!path_with_cmd)
		{
			free_arr(cmd_arr);
			free_arr(envp_arr);
			error_allocation_exec_struct_and_exit(exec_struct);
		}
	}
	return (path_with_cmd);
}

static char	**copy_cmd_arr(t_exec_substring *substring, \
t_exec_struct **exec_struct, char **envp_arr)
{
	char	**cmd_arr;

	cmd_arr = NULL;
	if (substring->cmd_arr)
	{
		cmd_arr = arr_copy(substring->cmd_arr);
		if (!cmd_arr)
		{
			free_arr(envp_arr);
			error_allocation_exec_struct_and_exit(exec_struct);
		}
	}
	return (cmd_arr);
}

void	exec_child(t_exec_substring *substring, char **envp_arr, \
t_exec_struct **exec_struct)
{
	int		exit_code;
	char	**cmd_arr;
	char	*path_with_cmd;

	cmd_arr = NULL;
	path_with_cmd = NULL;
	exit_code = exit_code_and_fd_handle_in_child(&substring, exec_struct);
	rl_clear_history();
	if (substring->exec_arguments && substring->fd_out > 0 && \
	substring->exec_arguments->is_builtin)
		exec_builtin(*exec_struct, substring, envp_arr);
	cmd_arr = copy_cmd_arr(substring, exec_struct, envp_arr);
	path_with_cmd = copy_path(substring, exec_struct, cmd_arr, envp_arr);
	free_before_execve(exec_struct);
	if (path_with_cmd && cmd_arr && cmd_arr[0] && exit_code == 0)
	{
		execve(path_with_cmd, cmd_arr, envp_arr);
		exit_code = 1;
		ft_putstr_fd("Execve failed\n", 2);
	}
	free(path_with_cmd);
	free_arr(cmd_arr);
	free_arr(envp_arr);
	exit(exit_code);
}
