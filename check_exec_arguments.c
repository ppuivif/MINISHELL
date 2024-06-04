#include "minishell.h"

void	check_exec_arguments(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
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
		error_allocation_exec_struct(exec_struct);
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

void	check_command_with_options(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char	**cmd_arr;

	cmd_arr = (*exec_substring)->cmd_arr;
	if (access(cmd_arr[0], F_OK) == 0)
	{
		(*exec_substring)->path_with_cmd = ft_strdup(cmd_arr[0]);
		if (!(*exec_substring)->path_with_cmd)
			error_allocation_exec_struct(exec_struct);
	}
	else
		check_path_in_envp(exec_substring, exec_struct);
}

static char	**build_envp_arr(t_exec_struct **exec_struct)
{
	char			**envp_arr;
	size_t			envp_arr_size;
	t_envp_struct	*tmp;
	size_t			i;

	envp_arr = NULL;
	envp_arr_size = ft_lst_size6((*exec_struct)->envp_struct);
	envp_arr = ft_calloc(envp_arr_size + 1, sizeof(char *));
	if (!envp_arr)
		error_allocation_exec_struct(exec_struct);
	tmp = (*exec_struct)->envp_struct;
	i = 0;
	while (tmp)
	{
		envp_arr[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	return (envp_arr);
}

static char	**search_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp[i] += 5;
			path = ft_split(envp[i], ':');
			return (path);
		}
		else
			i++;
	}
	return (path);
}

void	check_path_in_envp(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	int		return_value;
	char	**envp_arr;
	char	**path_envp;

	return_value = 0;
	envp_arr = build_envp_arr(exec_struct);
	path_envp = search_path(envp_arr);
	if (!path_envp || !path_envp[0])
	{
		ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		(*exec_struct)->command_line->exit_code = 127;
	}
	else
	{
		return_value = check_path_cmd_validity(path_envp, exec_substring);
		if (return_value == -1)
			error_allocation_exec_struct(exec_struct);
		if (return_value == 1)
		{
			ft_putstr_fd((*exec_substring)->cmd_arr[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			(*exec_struct)->command_line->exit_code = 127;
		}
		else
			(*exec_struct)->command_line->exit_code = 0;
	}
	free(envp_arr);
	envp_arr = NULL;
	free_arr(path_envp);
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
		if (access(path_with_cmd, F_OK) == 0)
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
