/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/29 21:55:36 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_code_last_process(int *pid_arr, int i)
{
	int		pid_last_process;
	int		status;
	int		exit_code_last_process;

	pid_last_process = pid_arr[i];
	status = 0;
	exit_code_last_process = 0;

	while (waitpid(pid_last_process, &status, 0) != -1)
		continue ;
	exit_code_last_process = WEXITSTATUS(status);
	i--;
	while (i >= 0)
	{
		while (waitpid(pid_arr[i], NULL, 0) != -1)
			continue;
		i--;
	}
	free(pid_arr);
	return (exit_code_last_process);
}

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
		envp_arr[i] = ft_strjoin_freed(envp_arr[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (envp_arr);
}

static int	search_last_input(t_exec_redirection *redirection, int fd_in)
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

static int	search_last_output(t_exec_redirection *redirection, int fd_out)
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
	free_and_null(pid_arr);
	return (new_pid_arr);
}

void	fd_handle(t_exec_substring **exec_substring)
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

int	fork_create(t_exec_struct **exec_struct, \
t_exec_substring *exec_substring, int *pid_arr)
{
	pid_t	pid_1;
	char **envp_arr;
	
	envp_arr = build_envp_arr(exec_struct);
	pid_1 = fork();
	if (pid_1 == -1)
	{
		free(pid_arr);
		perror("error\ncreate fork failed");
		error_fork_creation_and_exit(exec_struct);
	}
	if (pid_1 == 0)
		exec_child(exec_substring, envp_arr, exec_struct);
	free_arr(envp_arr);
	return (pid_1);
}

void	pipe_create(t_exec_struct **exec_struct, \
t_exec_substring **exec_substring, int *pid_arr)
{
	if (pipe((*exec_substring)->fd) == -1)
	{
		free(pid_arr);
		perror("error\ncreate pipe failed");
		error_pipe_creation_and_exit(exec_struct);
	}
	if ((*exec_substring)->fd_out == STDOUT_FILENO) //no out redirection
		(*exec_substring)->fd_out = (*exec_substring)->fd[1];
}

void	search_last_ioput(t_exec_substring **exec_substring)
{
	(*exec_substring)->fd_in = search_last_input( \
	(*exec_substring)->exec_redirections, (*exec_substring)->fd_in);
	(*exec_substring)->fd_out = search_last_output( \
	(*exec_substring)->exec_redirections, (*exec_substring)->fd_out);
}

void substrings_execution(t_exec_struct **exec_struct)
{
	int		i;
	int		*pid_arr;
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
		pid_arr[i] = fork_create(exec_struct, cursor, pid_arr);
		fd_handle(&cursor);
		cursor = cursor->next;
		i++;
	}
	(*exec_struct)->command_line->current_exit_code = \
	get_exit_code_last_process(pid_arr, i - 1);
}

void	execution(t_exec_struct **exec_struct)
{
	int					*fd_out;
	t_exec_substring	*cursor;

	cursor = (*exec_struct)->exec_substrings;
	fd_out = &cursor->fd_out;
	if (cursor->exec_arguments)
	{
		if (cursor->exec_redirections)
			*fd_out = search_last_output(cursor->exec_redirections, *fd_out);
		if (cursor->exec_arguments->is_builtin == IOPUT_NOT_ACCEPTED && \
		ft_lst_size7(cursor) == 1)
		{
			if (*fd_out > 0)
				exec_builtin(*exec_struct, cursor, NULL);
			return ;
		}
	}
	substrings_execution(exec_struct);
}

void	exec_child(t_exec_substring *substring, char **envp_arr, \
t_exec_struct **exec_struct)
{
	int		exit_code;
	char	**cmd_arr;
	char	*path_with_cmd;
	
	exit_code = 0;
	cmd_arr = NULL;
	path_with_cmd = NULL;

	
	if (substring->exec_arguments && substring->exec_arguments->is_argument_valid == false)
		exit_code = (*exec_struct)->command_line->current_exit_code;
	if (substring->fd_in == -1 || substring->fd_out == -1)
		exit_code = 1;
	if (substring->fd_in > 2)
	{
		dup2(substring->fd_in, STDIN_FILENO);
		close_fd(substring->fd_in);
	}
	if (substring->fd_out > 2)
	{
		dup2(substring->fd_out, STDOUT_FILENO);
		close_fd(substring->fd_out);
	}
	close_fd(substring->fd[0]);
	close_fd(substring->fd[1]);
	rl_clear_history();
	if (substring->exec_arguments && substring->fd_out > 0)
	{
		if (substring->exec_arguments->is_builtin)
			exec_builtin(*exec_struct, substring, envp_arr); //! J'ai mis ca
	}


	cmd_arr = arr_copy(substring->cmd_arr);
	if (!cmd_arr)
	{
		free_arr(envp_arr);
		error_allocation_exec_struct_and_exit(exec_struct);
	}

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

	free_envp_struct(&(*exec_struct)->envp_struct);//! J'ai mis ca
	free_all_command_line(&(*exec_struct)->command_line);//! J'ai mis ca
	free_all_exec_struct(exec_struct);//! J'ai mis ca
	if (path_with_cmd && cmd_arr && cmd_arr[0] && exit_code == 0)
	{
		execve(path_with_cmd, cmd_arr, envp_arr);
		perror("error\nexecve of a cmd failed");//to verify
			//exit_code = -1 ?
	}
	free(path_with_cmd);
	free_arr(cmd_arr);
	free_arr(envp_arr);
	exit(exit_code);
}
