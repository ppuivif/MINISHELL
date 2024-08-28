/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/28 18:38:59 by ppuivif          ###   ########.fr       */
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
//		if (cursor->next)
//			close_fd(cursor->fd_input);
		cursor = cursor->next;
	}
	return (fd_in);
}

static int	search_last_output(t_exec_redirection *redirection)
// recevoir en parametre fd_out par defaut a 1, idem search_last_input
{
	int					fd_out;
	t_exec_redirection	*cursor;

	fd_out = 1;
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
//		if (cursor->next)
//			close_fd(cursor->fd_output);
		cursor = cursor->next;
	}
	return (fd_out);
}

void	print_int_arr(int *arr, int size)// to delete
{
	int	i;

	i = 0;
	while (i <= size)
	{
		printf("arr %d : %d\n", i, arr[i]);
		i++;
	}
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

void	execution(t_exec_struct **exec_struct)
{
	t_exec_substring	*cursor;
	int					i;
	int					fd[2];
	pid_t				pid_1;
	int					fd_in;
	int					fd_out;
	int					substrings_nmemb;
	char				**envp_arr;
	int					status;
	int					*pid_arr;
	int					pid_last_process;

	cursor = (*exec_struct)->exec_substrings;
	substrings_nmemb = (int)ft_lst_size7(cursor);
	i = 0;
	status = 0;
	fd_in = STDIN_FILENO;
	pid_arr = NULL;
	pid_last_process = 0;
	fd[0] = 0;
	fd[1] = 1;
	if ((*exec_struct)->exec_substrings->exec_arguments)
	{
		fd_out = STDOUT_FILENO;//builtins don't use fd_in : to verify 
		if (cursor->exec_redirections)
			fd_out = search_last_output(cursor->exec_redirections);
		if ((*exec_struct)->exec_substrings->exec_arguments-> \
		is_builtin == 2 && substrings_nmemb == 1)
		{
			if (fd_out > 0)
				exec_builtin(*exec_struct, \
				(*exec_struct)->exec_substrings, NULL);
			return ;
		}
	}
	while (i < substrings_nmemb)
	{
		pid_arr = build_pid_arr(pid_arr, i);
		fd_out = STDOUT_FILENO;
		if (cursor->exec_redirections)
		{
			fd_in = search_last_input(cursor->exec_redirections, fd_in);
			fd_out = search_last_output(cursor->exec_redirections);
		}
		if (cursor != ft_lst_last7((*exec_struct)->exec_substrings))
		{
			if (pipe(fd) == -1)
			{
				free(pid_arr);
				perror("error\ncreate pipe failed");
				error_pipe_creation_and_exit(exec_struct);
			}
			if (fd_out == STDOUT_FILENO) //no out redirection
				fd_out = fd[1];
		}
		envp_arr = build_envp_arr(exec_struct);
		pid_1 = fork();
		if (pid_1 == -1)
		{
			free(pid_arr);
			perror("error\ncreate fork failed");
			error_fork_creation_and_exit(exec_struct);
		}
		pid_arr[i] = pid_1;
		pid_last_process = pid_1;
		if (pid_1 == 0)
		{
			exec_child(cursor, fd_in, fd_out, envp_arr, exec_struct, \
			pid_arr, fd);
		}
		close_fd(fd_in);
		close_fd(fd_out);
		if (cursor != ft_lst_last7((*exec_struct)->exec_substrings))
		{
			close_fd(fd[1]);
			fd_in = fd[0];
		}
		free_arr(envp_arr);
		cursor = cursor->next;
		i++;
	}
	while (waitpid(pid_last_process, &status, 0) != -1)
		continue ;
	(*exec_struct)->command_line->current_exit_code = WEXITSTATUS(status);
	i-=2;
	while (i >= 0)
	{
		while (waitpid(pid_arr[i], NULL, 0) != -1)
			continue;
		i--;
	}
	close_fd(fd[0]);
	close_fd(fd[1]);
	free(pid_arr);
}


void	exec_child(t_exec_substring *substring, int fd_in, int fd_out, char **envp_arr, t_exec_struct **exec_struct, int *pid_arr, int *fd)
{
	int		exit_code;
	char	*path_with_cmd;
	char	**cmd_arr;

	exit_code = 0;
	path_with_cmd = ft_strdup(substring->path_with_cmd);//malloc a proteger
	cmd_arr = arr_copy(substring->cmd_arr);
	if (substring->exec_arguments && substring->exec_arguments->is_argument_valid == false)
		exit_code = (*exec_struct)->command_line->current_exit_code;
	if (fd_in == -1 || fd_out == -1)
		exit_code = 1;
	if (fd_in > 2)
	{
		dup2(fd_in, STDIN_FILENO);
		close_fd(fd_in);
	}
	if (fd_out > 2)
	{
		dup2(fd_out, STDOUT_FILENO);
		close_fd(fd_out);
	}
	close_fd(fd[0]);
	close_fd(fd[1]);
	free(pid_arr);
	rl_clear_history();
	if (substring->exec_arguments && fd_out > 0)
	{
		if (substring->exec_arguments->is_builtin)
		{
			exec_builtin(*exec_struct, substring, envp_arr); //! J'ai mis ca
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
