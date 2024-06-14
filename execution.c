# include "minishell.h"

/*static void	unique_substring_execution(t_exec_substring *substring, t_exec_struct **exec_struct)
{
	char	**envp_arr;

	envp_arr = build_envp_arr(exec_struct);
	if (execve((*exec_struct)->exec_substrings->path_with_cmd, substring->cmd_arr, envp_arr) == -1)
		perror("error\nexecve of a cmd failed");//to verify
	error_execve_and_exit(exec_struct);//to verify
}*/

static int	search_definitive_input(t_exec_redirection *redirection, int fd_in)
{
	while (redirection)
	{
		if (redirection->fd_input != 0)
			fd_in = redirection->fd_input;
		redirection = redirection->next;
	}
	return (fd_in);
}
static int	search_definitive_output(t_exec_redirection *redirection)
{
	int	fd_out;

	fd_out = 1;
	while (redirection)
	{
		if (redirection->fd_output != 1)
			fd_out = redirection->fd_output;
		redirection = redirection->next;
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
	while (j <= i)
	{
		new_pid_arr[j] = pid_arr[j];
		j++;
	}
	free_and_null(pid_arr);
	return(new_pid_arr);
}

void	execution(t_exec_struct **exec_struct)
{
	t_exec_substring	*cursor;
	size_t		i;
	int		fd[2];
	pid_t	pid_1;
	int 	fd_in;
	int		fd_out;
	size_t	substrings_nmemb;
	char	**envp_arr;
//	int		status;
	int		*pid_arr;

	cursor = (*exec_struct)->exec_substrings;
	substrings_nmemb = ft_lst_size7(cursor);
//	printf("substrings nmemb : %ld", substrings_nmemb);
	i = 0;
//	status = 0;
	fd_in = STDIN_FILENO;
	pid_arr = NULL;
//	if (substrings_nmemb == 1)
//		unique_substring_execution(cursor, exec_struct);
	
	while (i < substrings_nmemb)
	{
		pid_arr = build_pid_arr(pid_arr, i);
//		printf("1 pid_arr[%ld] : %d\n", i, pid_arr[i]);
		fd_out = STDOUT_FILENO;
		if (cursor->exec_redirections)
		{
			fd_in = search_definitive_input(cursor->exec_redirections, fd_in);
			fd_out = search_definitive_output(cursor->exec_redirections);
		}
		if (cursor != ft_lst_last7((*exec_struct)->exec_substrings))
		{
			if (pipe(fd) == -1)
			{
				perror("error\ncreate pipe failed");
				error_pipe_creation_and_exit(exec_struct);
			}
			if (fd_out == STDOUT_FILENO)//no out redirection
				fd_out = fd[1];
		}
		envp_arr = build_envp_arr(exec_struct);
		pid_1 = fork();
		if (pid_1 == -1)
		{
			perror("error\ncreate fork failed");
			error_fork_creation_and_exit(exec_struct);
		}
		pid_arr[i] = pid_1;
		if (pid_1 == 0)
		{
//			exec_child(cursor, fd_in, fd_out, envp_arr, exec_struct);
//			printf("pid_arr[%ld] : %d\n", i, pid_arr[i]);
			exec_child(cursor, fd_in, fd_out, envp_arr);
			//return ?
		}	
		cursor = cursor->next;
		close_fd(fd_in);
		close_fd(fd_out);
	/*	if (cursor == ft_lst_last7((*exec_struct)->exec_substrings))
		{
			close_fd(fd[0]);
		}
		else*/
		if (substrings_nmemb != 1)
			close_fd(fd[1]);
		fd_in = fd[0];
		free_and_null(envp_arr);
		i++;
	}
//	printf("%s\n", strerror(errno));
//	while(waitpid(-1, &tmp, 0) != -1)
//	while(waitpid(-1, NULL, 0) != -1)
//		continue;
	i -= 1;
	while(waitpid(-1, NULL, 0) != -1)
	{
//			printf("j : %ld\n", i);
//			printf("number of childs : %ld\n", i);
//			printf("3 pid_arr[%ld] : %d\n", j, pid_arr[j]);
		
/*		if (waitpid(pid_arr[i], &status, 0))
		{
			printf("exit_code : %d\n", WEXITSTATUS(status));
		}*/
		continue;
	}

}

//void	exec_child(t_exec_substring *substrings, int fd_in, int fd_out, char **envp, t_exec_struct **exec_struct)
void	exec_child(t_exec_substring *substrings, int fd_in, int fd_out, char **envp)
{
	
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_fd(fd_in);
	close_fd(fd_out);
	while (substrings->exec_redirections)
	{
		close_fd(substrings->exec_redirections->fd_output);
		close_fd(substrings->exec_redirections->fd_input);
		substrings->exec_redirections = substrings->exec_redirections->next;
	}
	if (substrings->path_with_cmd && substrings->cmd_arr \
	&& substrings->cmd_arr[0])
	{
		if (execve(substrings->path_with_cmd, substrings->cmd_arr, envp) == -1)
			perror("error\nexecve of a cmd failed");//to verify
	}
//	error_execve_and_exit(exec_struct);//to verify
}