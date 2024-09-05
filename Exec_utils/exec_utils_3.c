/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 20:07:03 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_envp_arr(t_exec_struct **exec_struct)
{
	char			**envp_arr;
	size_t			envp_arr_size;
	t_envp_struct	*tmp;
	size_t			i;

	envp_arr = NULL;
	envp_arr_size = ft_lst_size6((*exec_struct)->envp_struct);
	envp_arr = ft_calloc(envp_arr_size + 1, sizeof(char *));
	if (!envp_arr)
		error_allocation_exec_struct_and_exit(exec_struct);
	tmp = (*exec_struct)->envp_struct;
	i = 0;
	while (tmp)
	{
		envp_arr[i] = ft_strjoin(tmp->name, "=");
		if (tmp->value)
			envp_arr[i] = ft_strjoin_freed(envp_arr[i], tmp->value);
		else
			envp_arr[i] = ft_strjoin_freed(envp_arr[i], "");
		tmp = tmp->next;
		i++;
	}
	return (envp_arr);
}

int	search_last_input(t_exec_redirection *redirection, int fd_in)
{
	t_exec_redirection	*cursor;

	cursor = redirection;
	while (cursor)
	{
		if (cursor->fd_input == -1)
		{
			fd_in = cursor->fd_input;
			break ;
		}
		if (cursor->fd_input > 2)
			fd_in = cursor->fd_input;
		cursor = cursor->next;
	}
	return (fd_in);
}

int	search_last_output(t_exec_redirection *redirection, int fd_out)
{
	t_exec_redirection	*cursor;

	cursor = redirection;
	while (cursor)
	{
		if (cursor->fd_output == -1)
		{
			fd_out = cursor->fd_output;
			break ;
		}
		if (cursor->fd_output > 2)
			fd_out = cursor->fd_output;
		cursor = cursor->next;
	}
	return (fd_out);
}

void	fd_handle_in_parent(t_exec_substring **exec_substring)
{
	close_fd((*exec_substring)->fd_in);
	close_fd((*exec_substring)->fd_out);
	if ((*exec_substring)->next)
	{
		close_fd((*exec_substring)->fd[1]);
		(*exec_substring)->next->fd_in = (*exec_substring)->fd[0];
		(*exec_substring)->next->fd_out = STDOUT_FILENO;
		(*exec_substring)->next->fd[0] = (*exec_substring)->fd[0];
	}
	else
	{
		close_fd((*exec_substring)->fd[0]);
		close_fd((*exec_substring)->fd[1]);
	}
}

int	get_exit_code_last_process(int *pid_arr, int i)
{
	int		status;
	int		exit_code_last_process;
	int		index_last_process;

	status = 0;
	exit_code_last_process = 0;
	index_last_process = i;
	while (i >= 0)
	{
		while (waitpid(pid_arr[i], &status, 0) != -1)
			continue ;
		if (i == index_last_process)
		{
			if (WIFSIGNALED(status))
				exit_code_last_process = 128 + WTERMSIG(status);
			else
				exit_code_last_process = WEXITSTATUS(status);
		}
		i--;
	}
	return (exit_code_last_process);
}
