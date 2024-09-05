/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_17.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 10:20:17 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_permission_on_cmd_with_path(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": permission denied\n", 2);
	(*exec_struct)->command_line->current_exit_code = 126;
	(*exec_substring)->exec_arguments->is_argument_valid = false;
}

static void	no_valid_argument(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	if (ft_strcspn((*exec_substring)->cmd_arr[0], "/") < \
	(int)ft_strlen((*exec_substring)->cmd_arr[0]))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	(*exec_struct)->command_line->current_exit_code = 127;
	(*exec_substring)->exec_arguments->is_argument_valid = false;
}

static int	check_permission_on_path_with_cmd(char **path_envp, \
char *path_with_cmd, t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	if (access(path_with_cmd, F_OK) == 0)
	{
		(*exec_substring)->path_with_cmd = ft_strdup(path_with_cmd);
		if (!(*exec_substring)->path_with_cmd)
		{
			path_envp = free_arr(path_envp);
			error_allocation_exec_struct_and_exit(exec_struct);
		}
		free (path_with_cmd);
		return (0);
	}
	if (errno == EACCES)
	{
		free (path_with_cmd);
		return (2);
	}
	return (1);
}

static int	check_path_cmd_validity(char **path_envp, \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	char	*path_with_cmd;
	int		status_code;

	status_code = 0;
	while (*path_envp)
	{
		path_with_cmd = NULL;
		path_with_cmd = ft_strjoin(*path_envp, "/");
		path_with_cmd = ft_strjoin_freed(path_with_cmd, \
		(*exec_substring)->cmd_arr[0]);
		if (!path_with_cmd)
		{
			path_envp = free_arr(path_envp);
			error_allocation_exec_struct_and_exit(exec_struct);
		}
		status_code = check_permission_on_path_with_cmd(path_envp, \
		path_with_cmd, exec_substring, exec_struct);
		if (status_code == 0)
			return (0);
		if (status_code == 2)
			return (2);
		free (path_with_cmd);
		path_envp ++;
	}
	return (1);
}

void	check_when_path_exists(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct, char **path_envp)
{
	int		status_code;

	status_code = 0;
	if (!(*exec_substring)->cmd_arr[0] || !(*exec_substring)->cmd_arr[0][0])
		status_code = 1;
	else
		status_code = check_path_cmd_validity(path_envp, exec_substring, \
		exec_struct);
	if (status_code == 0)
		(*exec_struct)->command_line->current_exit_code = 0;
	else if (status_code == 1)
		no_valid_argument(exec_substring, exec_struct);
	else if (status_code == 2)
		no_permission_on_cmd_with_path(exec_substring, exec_struct);
}
