/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 10:13:52 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_fork_create(t_exec_struct **exec_struct, \
t_exec_substring *exec_substring, int *pid_arr)
{
	pid_t	pid_1;
	char	**envp_arr;

	envp_arr = build_envp_arr(exec_struct);
	pid_1 = fork();
	if (pid_1 == -1)
	{
		free_arr(envp_arr);
		free(pid_arr);
		perror("error\ncreate fork failed");
		error_fork_creation_and_exit(exec_struct);
	}
	exec_substring->pid_arr = pid_arr;
	if (pid_1 == 0)
		exec_child(exec_substring, envp_arr, exec_struct);
	free_arr(envp_arr);
	return (pid_1);
}

static void	pipe_create(t_exec_struct **exec_struct, \
t_exec_substring **exec_substring, int *pid_arr)
{
	if (pipe((*exec_substring)->fd) == -1)
	{
		free(pid_arr);
		perror("error\ncreate pipe failed");
		error_pipe_creation_and_exit(exec_struct);
	}
	if ((*exec_substring)->fd_out == STDOUT_FILENO)
		(*exec_substring)->fd_out = (*exec_substring)->fd[1];
}

static void	search_last_ioput(t_exec_substring **exec_substring)
{
	(*exec_substring)->fd_in = search_last_input \
	((*exec_substring)->exec_redirections, (*exec_substring)->fd_in);
	(*exec_substring)->fd_out = search_last_output \
	((*exec_substring)->exec_redirections, (*exec_substring)->fd_out);
}

static int	*build_pid_arr(int *pid_arr, int i)
{
	int	*new_pid_arr;
	int	j;

	new_pid_arr = NULL;
	j = 0;
	new_pid_arr = malloc((i + 1) * sizeof(int));
	if (!new_pid_arr)
		exit (EXIT_FAILURE);
	if (!pid_arr)
	{
		new_pid_arr[0] = 0;
		return (new_pid_arr);
	}
	while (j < i)
	{
		new_pid_arr[j] = pid_arr[j];
		j++;
	}
	new_pid_arr[j] = 0;
	return (new_pid_arr);
}

void	substrings_execution(t_exec_struct **exec_struct)
{
	int					i;
	int					*pid_arr;
	t_exec_substring	*cursor;

	i = 0;
	pid_arr = NULL;
	cursor = (*exec_struct)->exec_substrings;
	while (cursor)
	{
		pid_arr = build_pid_arr(pid_arr, i);
		if (cursor->exec_redirections)
			search_last_ioput(&cursor);
		if (cursor != ft_lst_last7((*exec_struct)->exec_substrings))
			pipe_create(exec_struct, &cursor, pid_arr);
		pid_arr[i] = exec_fork_create(exec_struct, cursor, pid_arr);
		fd_handle_in_parent(&cursor);
		cursor = cursor->next;
		i++;
	}
	(*exec_struct)->command_line->current_exit_code = \
	get_exit_code_last_process(pid_arr, i - 1);
}
