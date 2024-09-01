/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/28 14:57:47 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_not_a_file(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(*exec_substring)->exec_arguments->is_argument_valid = false;
	(*exec_struct)->command_line->current_exit_code = 127;
}

static void	is_not_an_executable_file(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	(*exec_substring)->exec_arguments->is_argument_valid = false;
	(*exec_struct)->command_line->current_exit_code = 126;
}

static void	is_an_executable_file(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct, char **path_envp)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin("./", (*exec_substring)->cmd_arr[0]);
	if (!tmp)
	{
		path_envp = free_arr(path_envp);
		error_allocation_exec_struct_and_exit(exec_struct);
	}
	(*exec_substring)->path_with_cmd = ft_strdup(tmp);
	if (!tmp)
	{
		path_envp = free_arr(path_envp);
		error_allocation_exec_struct_and_exit(exec_struct);
	}
	(*exec_struct)->command_line->current_exit_code = 0;
	tmp = free_and_null(tmp);
}

void	check_when_no_path(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct, char **path_envp)
{
	if (access((*exec_substring)->cmd_arr[0], F_OK) == 0)
	{
		if (access((*exec_substring)->cmd_arr[0], X_OK) == 0)
			is_an_executable_file(exec_substring, exec_struct, path_envp);
		else
			is_not_an_executable_file(exec_substring, exec_struct);
	}
	else
		is_not_a_file(exec_substring, exec_struct);
}
