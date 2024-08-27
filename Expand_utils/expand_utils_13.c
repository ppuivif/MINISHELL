/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_13.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/27 12:08:43 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_a_reachable_directory(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	(*exec_substring)->exec_arguments->is_argument_valid = false;
	(*exec_struct)->command_line->current_exit_code = 126;
}

static void	is_a_file_without_rights( \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": Permission denied1\n", 2);
	(*exec_substring)->exec_arguments->is_argument_valid = false;
	(*exec_struct)->command_line->current_exit_code = 126;
}

static void	is_a_reachable_file_with_complete_path( \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	(*exec_substring)->path_with_cmd = \
	ft_strdup((*exec_substring)->cmd_arr[0]);
	if (!(*exec_substring)->path_with_cmd)
		error_allocation_exec_struct_and_exit(exec_struct);
}

static void	is_a_non_reachable_directory_or_path( \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	ft_putstr_fd(": Permission denied2\n", 2);
	(*exec_substring)->exec_arguments->is_argument_valid = false;
	(*exec_struct)->command_line->current_exit_code = 126;
}

int	check_dir_and_file_permission(char **cmd_arr, \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	struct stat	buffer;

	if (strcspn(cmd_arr[0], "/") < ft_strlen(cmd_arr[0]) && \
	stat(cmd_arr[0], &buffer) == 0)
	{
		if (S_ISDIR(buffer.st_mode))
			is_a_reachable_directory(exec_substring, exec_struct);
		else if (S_ISREG(buffer.st_mode))
		{
			if (!(buffer.st_mode & S_IXUSR))
				is_a_file_without_rights(exec_substring, \
				exec_struct);
			else
				is_a_reachable_file_with_complete_path(exec_substring, \
				exec_struct);
		}
		return (0);
	}
	else if (errno == EACCES)
	{
		is_a_non_reachable_directory_or_path(exec_substring, exec_struct);
		return (0);
	}
	return (1);
}
