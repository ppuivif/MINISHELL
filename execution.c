# include "minishell.h"

/*static void	unique_substring_execution(t_exec_substring *substring, t_exec_struct **exec_struct)
{
	char	**envp_arr;

	envp_arr = build_envp_arr(exec_struct);
	if (execve((*exec_struct)->exec_substrings->path_with_cmd, substring->cmd_arr, envp_arr) == -1)
		perror("error\nexecve of a cmd failed");//to verify
	error_execve_and_exit(exec_struct);//to verify
}*/

static int	search_last_input(t_exec_redirection *redirection, int fd_in)
{
	t_exec_redirection	*cursor;

	cursor = redirection;
	while (cursor)
	{
		if (cursor->fd_input == -1)
		{
			fd_in = cursor->fd_input;
			break;
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
{
	int	fd_out;
	t_exec_redirection	*cursor;

	fd_out = 1;
	cursor = redirection;
	while (cursor)
	{
		if (cursor->fd_output == -1)
		{
			fd_out = cursor->fd_output;
			break;
		}
		if (cursor->fd_output > 2)
			fd_out = cursor->fd_output;
//		if (cursor->next)
//			close_fd(cursor->fd_output);
		cursor = cursor->next;
	}
	return (fd_out);
}

void print_int_arr(int *arr, int size)
{
	int i;

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
		//new_pid_arr[1] = 0;
		return (new_pid_arr);
	}
	while (j < i)
	{
		new_pid_arr[j] = pid_arr[j];
		j++;
	}
	new_pid_arr[j] = 0;
	free_and_null(pid_arr);
	return(new_pid_arr);
}


static bool is_fd_open(int fd) {
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1 && errno == EBADF) {
        return (false);  // File descriptor is closed
    }
    return (true);  // File descriptor is open
}



void	execution(t_exec_struct **exec_struct)
{
	t_exec_substring	*cursor;
	int		i;
	int		fd[2];
	pid_t	pid_1;
	int 	fd_in;
	int		fd_out;
	int		substrings_nmemb;
	char	**envp_arr;
	int		status;
	int		*pid_arr;
	int		pid_last_process;
		
	cursor = (*exec_struct)->exec_substrings;
	substrings_nmemb = (int)ft_lst_size7(cursor);
//	printf("substrings nmemb : %ld", substrings_nmemb);
	i = 0;
	status = 0;
	fd_in = STDIN_FILENO;
	pid_arr = NULL;
	pid_last_process = 0;
	fd[0] = 0;
	fd[1] = 1;

//	if (substrings_nmemb == 1)
//		unique_substring_execution(cursor, exec_struct);
	
	while (i < substrings_nmemb)
	{
		pid_arr = build_pid_arr(pid_arr, i);
//		printf("1 pid_arr[%ld] : %d\n", i, pid_arr[i]);
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
			if (fd_out == STDOUT_FILENO)//no out redirection
				fd_out = fd[1];
			printf("status fd[0] value : %d - open : %s\n", fd[0], is_fd_open(fd[0]) ? "true" : "false");	
			printf("status fd[1] value : %d - open : %s\n", fd[1], is_fd_open(fd[1]) ? "true" : "false");	
		}

		envp_arr = build_envp_arr(exec_struct);

	//	if (substrings_nmemb != 1)
	//		close_fd(fd[1]);


		printf("status fd_in value : %d - open : %s\n", fd_in, is_fd_open(fd_in) ? "true" : "false");	
		printf("status fd_out value : %d - open : %s\n", fd_out, is_fd_open(fd_out) ? "true" : "false");

		pid_1 = fork();
		if (pid_1 == -1)
		{
			free(pid_arr);
			perror("error\ncreate fork failed");
			error_fork_creation_and_exit(exec_struct);
		}
		pid_arr[i] = pid_1;
		pid_last_process = pid_1;

//		printf("pid : %d\n", pid_1);
//		printf("pid_arr[%d] : %d\n", i, pid_arr[i]);



		if (pid_1 == 0)
		{
			exec_child(cursor, fd_in, fd_out, envp_arr, exec_struct, pid_arr, fd);
		}
	/*	if (cursor == ft_lst_last7((*exec_struct)->exec_substrings))
		{
			close_fd(fd[0]);
		}
		else*/

		if (substrings_nmemb != 1 && cursor == ft_lst_last7((*exec_struct)->exec_substrings))
		{
			close_fd(fd[0]);
//			close_fd(fd[1]);
		}

		close_fd(fd_in);
		close_fd(fd_out);
		fd_in = fd[0];
		free_arr(envp_arr);
		cursor = cursor->next;
		i++;
		
		printf("status fd_in value after parent : %d - open : %s\n", fd_in, is_fd_open(fd_in) ? "true" : "false");	
		printf("status fd_out value after parent : %d - open : %s\n\n", fd_out, is_fd_open(fd_out) ? "true" : "false");	

	}
//	printf("%s\n", strerror(errno));
//	while(waitpid(-1, &tmp, 0) != -1)
//	while(waitpid(-1, NULL, 0) != -1)
//		continue;
	
//	wait_return = waitpid(pid_last_process, &status, 0);




/*	cursor = (*exec_struct)->exec_substrings;
	while (cursor->exec_redirections)
	{
		close_fd(cursor->exec_redirections->fd_output);
		close_fd(cursor->exec_redirections->fd_input);
		cursor->exec_redirections = cursor->exec_redirections->next;
	}*/


	while (waitpid(pid_last_process, &status, 0) != -1)
		continue;
//	printf("wexitstatus : %d\n", WEXITSTATUS(status));
	(*exec_struct)->command_line->current_exit_code = WEXITSTATUS(status);
	i-=2;

	while ( i >= 0)
	{
//		printf("i : %d\n", i);
//		print_int_arr(pid_arr, i);
		while (waitpid(pid_arr[i], NULL, 0) != -1)
			continue;
		i--;
	}

/*	while (wait_return != -1)
	{
		wait_return = wait(&status);
//		if (WIFEXITED(status))
//		else
//			return EXIT_FAILURE;
		if (wait_return == pid_last_process)
		{
//			printf("pid_arr[i] : %d\n", pid_arr[i]);
			//printf("here");
//			printf("wexitstatus : %d\n", WEXITSTATUS(status));
			(*exec_struct)->command_line->current_exit_code = WEXITSTATUS(status);
		}
	}*/

	free(pid_arr);
}


//void	exec_child(t_exec_substring *substrings, int fd_in, int fd_out, char **envp, t_exec_struct **exec_struct)
void	exec_child(t_exec_substring *substring, int fd_in, int fd_out, char **envp_arr, t_exec_struct **exec_struct, int *pid_arr, int *fd)
{
	int	exit_code;
	char *path_with_cmd;
	char **cmd_arr;

	exit_code = 0;
	path_with_cmd = ft_strdup(substring->path_with_cmd);//malloc a proteger
	cmd_arr = arr_copy(substring->cmd_arr);

	if (substring->exec_arguments && substring->exec_arguments->is_argument_valid == false)
		exit_code = (*exec_struct)->command_line->current_exit_code;
	if (fd_in == -1 || fd_out == -1)
		exit_code = 1;
	if (fd[0] != 0 && fd[1] != 1)
	{
		close_fd(fd[0]);
		close_fd(fd[1]);
	}
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
	free(pid_arr);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	free_all_exec_struct(exec_struct);
	clear_history();
	if (path_with_cmd && cmd_arr && cmd_arr[0] && exit_code == 0)
	{
		if (execve(path_with_cmd, cmd_arr, envp_arr) == -1)
			perror("error\nexecve of a cmd failed");//to verify
			//exit_code = -1 ?
	}
//	printf("exit_code : %d\n", exit_code);
//	free(pid_arr);
//	free_envp_struct(&(*exec_struct)->envp_struct);
//	free_all_command_line(&(*exec_struct)->command_line);
//	free_all_exec_struct(exec_struct);

//	clear_history();
	free(path_with_cmd);
	free_arr(cmd_arr);
	free_arr(envp_arr);
	exit(exit_code);
//	error_execve_and_exit(exec_struct);//to verify
}