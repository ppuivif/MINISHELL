#include "minishell.h"

void	check_exec_arguments(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	if ((*exec_substring)->exec_arguments->argument)
	{
		if (check_is_builtin((*exec_substring)->exec_arguments))
			return ;
	}
	build_cmd_arr(exec_substring, exec_struct);
	if ((*exec_substring)->cmd_arr && (*exec_substring)->cmd_arr[0])
		check_command_with_options(exec_substring, exec_struct);
}

void	build_cmd_arr(t_exec_substring **exec_substring, \
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


/*static bool is_part_of_envp_path(char *cmd_arr_0, t_exec_struct **exec_struct)
{
	char	**envp_arr;
	char	**path_envp;
	size_t	cmd_arr_0_len;
	int		i;

	i = 0;
	envp_arr = build_envp_arr(exec_struct);
	path_envp = search_path(envp_arr);
	cmd_arr_0_len = ft_strlen(cmd_arr_0);
	if (!path_envp || !path_envp[0])
	{
		envp_arr = free_and_null(envp_arr);
		free_arr(path_envp);	
		return (false);
	}
	else
	{
		while (path_envp[i])
		{
			if (ft_strncmp(cmd_arr_0, path_envp[i], cmd_arr_0_len) == 0)
			{
				envp_arr = free_and_null(envp_arr);
				free_arr(path_envp);
				return (true);
			}
			i++;
		}
	}
	envp_arr = free_and_null(envp_arr);
	free_arr(path_envp);
	return (false);
}*/

static void	check_dir(char *cmd_arr_0, t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	if (strcspn(cmd_arr_0, "/") < ft_strlen(cmd_arr_0))
	{
		ft_putstr_fd(cmd_arr_0, 2);
		if (access(cmd_arr_0, X_OK) == 0)//F_OK to verify if file exists, X_OK to verify if the file is executable
		{
			ft_putstr_fd(": Is a directory\n", 2);
			(*exec_struct)->command_line->current_exit_code = 126;
		}
		else
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			(*exec_struct)->command_line->current_exit_code = 127;
		}
		(*exec_substring)->exec_arguments->is_argument_valid = false;
	}
	else//for temp
	{
		ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		(*exec_substring)->exec_arguments->is_argument_valid = false;
		(*exec_struct)->command_line->current_exit_code = 127;
	}
}

/*		if (access(cmd_arr_0, X_OK) == 0)//F_OK to verify if file exists, X_OK to verify if the file is executable
		{
			if ((cmd_arr_0[0]  == '.' && cmd_arr_0[1] == '/') || \
			strcspn(cmd_arr_0, "/") == ft_strlen(cmd_arr_0) - 1 || \
			is_part_of_envp_path(cmd_arr_0, exec_struct) == true)
//			is_envp_variable)
			{
				ft_putstr_fd(cmd_arr_0, 2);
				ft_putstr_fd(": Is a directory\n", 2);
				(*exec_struct)->command_line->current_exit_code = 126;
				(*exec_substring)->exec_arguments->is_argument_valid = false;
			}
		}
		else
		{
			ft_putstr_fd(cmd_arr_0, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			(*exec_substring)->exec_arguments->is_argument_valid = false;
			(*exec_struct)->command_line->current_exit_code = 127;
		}*/


void	check_command_with_options(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char	**cmd_arr;
	DIR		*dir;

	dir = NULL;
	cmd_arr = (*exec_substring)->cmd_arr;
	dir = opendir(cmd_arr[0]);
	if (dir)
	{
		check_dir(cmd_arr[0], exec_substring, exec_struct);
		closedir(dir);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		(*exec_substring)->exec_arguments->is_argument_valid = false;
		(*exec_struct)->command_line->current_exit_code = 126;
	}
	else if (access(cmd_arr[0], X_OK) == 0)//F_OK to verify if file exists, X_OK to verify if the file is executable
	{
		(*exec_substring)->path_with_cmd = ft_strdup(cmd_arr[0]);
		if (!(*exec_substring)->path_with_cmd)
			error_allocation_exec_struct_and_exit(exec_struct);
	}
	else
		check_path_in_envp(exec_substring, exec_struct);
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

/*char	**search_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(&envp[i][5], ':');
			return (path);
		}
		else
			i++;
	}
	return (path);
}*/

char	**search_path(t_envp_struct *envp_struct)
{
	char			**path;
	t_envp_struct	*cursor;

	path = NULL;
	cursor = envp_struct;
	while (cursor)
	{
		if (ft_strncmp(cursor->name, "PATH", 4) == 0)
		{
			path = ft_split(cursor->value, ':');
			return (path);
		}
		cursor = cursor->next;
	}
	return (path);
}

void	check_path_in_envp(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	int		return_value;
//	char	**envp_arr;
	char	**path_envp;

	return_value = 0;
//	envp_arr = build_envp_arr(exec_struct);
//	path_envp = search_path(envp_arr);
	path_envp = search_path((*exec_struct)->envp_struct);
	if (!path_envp || !path_envp[0])
	{
		ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		(*exec_substring)->exec_arguments->is_argument_valid = false;
		(*exec_struct)->command_line->current_exit_code = 127;
	}
	else
	{
		if ((*exec_substring)->cmd_arr[0][0] == 0)
			return_value = 1;
		else
			return_value = check_path_cmd_validity(path_envp, exec_substring);
		if (return_value == -1)
			error_allocation_exec_struct_and_exit(exec_struct);
		if (return_value == 1)
		{
			ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
			if (strcspn((*exec_substring)->cmd_arr[0], "/") < ft_strlen((*exec_substring)->cmd_arr[0]))
				ft_putstr_fd(": No such file or directory\n", 2);
			else
				ft_putstr_fd(": command not found\n", 2);
			(*exec_substring)->exec_arguments->is_argument_valid = false;
			(*exec_struct)->command_line->current_exit_code = 127;
		}
		else
			(*exec_struct)->command_line->current_exit_code = 0;
	}
//	envp_arr = free_arr(envp_arr);
	path_envp = free_arr(path_envp);
}

int	check_path_cmd_validity(char **path, t_exec_substring **exec_substring)
{
	char	*path_with_cmd;
	char	**cmd_arr;

	cmd_arr = (*exec_substring)->cmd_arr;
	while (*path)
	{
		path_with_cmd = NULL;
		path_with_cmd = ft_strjoin(*path, "/");
		path_with_cmd = ft_strjoin_freed(path_with_cmd, cmd_arr[0]);
		if (!path_with_cmd || !path_with_cmd[0])
			return (1);
		if (access(path_with_cmd, X_OK) == 0)
		{
			(*exec_substring)->path_with_cmd = ft_strdup(path_with_cmd);
			if (!(*exec_substring)->path_with_cmd)
				return (-1);
			free (path_with_cmd);
			return (0);
		}
		free (path_with_cmd);
		path ++;
	}
	return (1);
}
