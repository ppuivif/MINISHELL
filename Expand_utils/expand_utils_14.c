/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_14.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/27 18:37:05 by ppuivif          ###   ########.fr       */
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

static void	empty_cmd_with_path(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
	if (strcspn((*exec_substring)->cmd_arr[0], "/") < \
	ft_strlen((*exec_substring)->cmd_arr[0]))
		ft_putstr_fd(": No such file or directory\n", 2);//for /missing or missing or "< temp/infile.txt"
	else
		ft_putstr_fd(": command not found\n", 2);
	(*exec_struct)->command_line->current_exit_code = 127;
	(*exec_substring)->exec_arguments->is_argument_valid = false;
}

static int	check_permission_on_path_with_cmd(char **path_envp, \
char *path_with_cmd, t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	if (access(path_with_cmd, F_OK) == 0) //(access(path_with_cmd, X_OK)==0)
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
	char	**cmd_arr;
	int		return_value;

	cmd_arr = (*exec_substring)->cmd_arr;
	return_value = 0;
	while (*path_envp)
	{
		path_with_cmd = NULL;
		path_with_cmd = ft_strjoin(*path_envp, "/");
		path_with_cmd = ft_strjoin_freed(path_with_cmd, cmd_arr[0]);
		if (!path_with_cmd)
		{
			path_envp = free_arr(path_envp);
			error_allocation_exec_struct_and_exit(exec_struct);
		}
		if (!path_with_cmd[0])
			return (1);
		return_value = check_permission_on_path_with_cmd(path_envp, \
		path_with_cmd, exec_substring, exec_struct);
		if (return_value == 0)
			return (0);
		if (return_value == 2)
			return (2);
		free (path_with_cmd);
		path_envp ++;
	}
	return (1);
}

static void	check_when_path_exists(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct, char **path_envp)
{
	int		status_code;

	status_code = 0;
	if ((*exec_substring)->cmd_arr[0][0] == 0)
		status_code = 1;
	else
		status_code = check_path_cmd_validity(path_envp, exec_substring, exec_struct);
	if (status_code == 0)
		(*exec_struct)->command_line->current_exit_code = 0;
	else if (status_code == 1)
		empty_cmd_with_path(exec_substring, exec_struct);		
	else if (status_code == 2)
		no_permission_on_cmd_with_path(exec_substring, exec_struct);
}

static void	check_when_no_path(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct, char **path_envp)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin("./", (*exec_substring)->cmd_arr[0]);// for minishell
	if (!tmp)
	{
		path_envp = free_arr(path_envp);
		error_allocation_exec_struct_and_exit(exec_struct);
	}
	(*exec_substring)->path_with_cmd = ft_strdup(tmp);
	if (!tmp)
		error_allocation_exec_struct_and_exit(exec_struct);
	if (access(tmp, F_OK) == 0)
	{
		(*exec_struct)->command_line->current_exit_code = 0;
		tmp = free_and_null(tmp);
	}
	else
	{
		ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		(*exec_substring)->exec_arguments->is_argument_valid = false;
		(*exec_struct)->command_line->current_exit_code = 127;
	}
}

static char	**search_path(t_exec_struct **exec_struct)
{
	char			**path;
	t_envp_struct	*cursor;

	path = NULL;
	cursor = (*exec_struct)->envp_struct;
	while (cursor)
	{
		if (ft_strcmp(cursor->name, "PATH") == 0)
		{
			path = ft_split(cursor->value, ':');
			if (!path)
				error_allocation_exec_struct_and_exit(exec_struct);
			return (path);
		}
		cursor = cursor->next;
	}
	return (path);
}

void	check_path_in_envp(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char	**path_envp;

	path_envp = search_path(exec_struct);
	if (!path_envp || !path_envp[0])
		check_when_no_path(exec_substring, exec_struct, path_envp);
	else
		check_when_path_exists(exec_substring, exec_struct, path_envp);
	path_envp = free_arr(path_envp);
}
