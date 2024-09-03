/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:35 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/03 06:24:05 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_command_with_options(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char		**cmd_arr;

	cmd_arr = (*exec_substring)->cmd_arr;
	if (check_dir_and_file_permission(cmd_arr, exec_substring, \
	exec_struct) == 0)
		return ;
	else if (ft_strcmp(cmd_arr[0], ".") == 0)
	{
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd(": filename argument required\n", 2);
		(*exec_struct)->command_line->current_exit_code = 2;
		(*exec_substring)->exec_arguments->is_argument_valid = false;
	}
	else if (ft_strcmp(cmd_arr[0], "..") == 0)
	{
		ft_putstr_fd(cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		(*exec_struct)->command_line->current_exit_code = 127;
		(*exec_substring)->exec_arguments->is_argument_valid = false;
	}
	else
		check_path_in_envp(exec_substring, exec_struct);
}

static void	build_cmd_arr(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char			**cmd_arr;
	size_t			cmd_arr_size;
	t_exec_argument	*tmp;
	size_t			i;	

	cmd_arr = NULL;
	cmd_arr_size = ft_lst_size9((*exec_substring)->exec_arguments);
	cmd_arr = ft_calloc(cmd_arr_size + 1, sizeof(char *));
	if (!cmd_arr)
		error_allocation_exec_struct_and_exit(exec_struct);
	tmp = (*exec_substring)->exec_arguments;
	i = 0;
	while (tmp)
	{
		cmd_arr[i] = tmp->argument;
		tmp = tmp->next;
		i++;
	}
	(*exec_substring)->cmd_arr = cmd_arr;
}

void	check_exec_arguments(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	if ((*exec_substring)->exec_arguments->argument && \
	(*exec_struct)->command_line->current_exit_code == 0)
	{
		if (check_is_builtin((*exec_substring)->exec_arguments))
		{
			(*exec_struct)->command_line->current_exit_code = 0;
			return ;
		}
		build_cmd_arr(exec_substring, exec_struct);
		if ((*exec_substring)->cmd_arr && (*exec_substring)->cmd_arr[0])
			check_command_with_options(exec_substring, exec_struct);
	}
}
