#include "minishell.h"

//int	check_commands(t_exec_subline **exec_subline, t_command_line **command_line, t_exec_struct **exec_struct)
int	check_commands(t_command_line **command_line, t_exec_struct **exec_struct)
{
	char	**envp_arr;

	envp_arr = build_envp_arr(exec_struct, command_line);
//	build_full_path_cmd_arr(exec_subline, envp_arr);
	free_arr(envp_arr);
	return (0);



}

char	**build_envp_arr(t_exec_struct **exec_struct, t_command_line **command_line)
{
	char			**envp_arr;
	size_t			arr_size;
	t_envp_struct	*tmp;
	size_t			i;

	envp_arr = NULL;
	arr_size = ft_lst_size6((*exec_struct)->envp_struct);
	envp_arr = ft_calloc(arr_size, sizeof(char *));
	if (!envp_arr)
		error_allocation_exec_struct(exec_struct, command_line);
	tmp = (*exec_struct)->envp_struct->next;
	i = 0;
	while (tmp)
	{
		envp_arr[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
//	envp_arr[0] = ft_strdup("");
	return (envp_arr);
}

/*void	build_full_path_cmd_arr(t_exec_subline **exec_subline, char **envp)
{




}


void	build_full_path_cmd_arr(char **argv, char **envp,
		t_main_struct *main_struct)
{
	int	i;

	i = 2;
	while (i < main_struct->nb_arg)
	{
		t_cmd	*new_cmd;
		char	**cmd_arr;
		char	*path_cmd;
		
		cmd_arr = NULL;
		path_cmd = NULL;
		build_cmd_arr(argv[i], &cmd_arr, &path_cmd, envp);
		new_cmd = ft_lst_dc_new(cmd_arr, path_cmd);
		ft_lst_dc_add_back(&main_struct->head, new_cmd);
		i++;
	}
//	ft_lst_dc_print(main_struct->head);
}

void	build_cmd_arr(char *argv, char ***cmd_arr, char	**cmd_path, char **envp)
{
	*cmd_arr = ft_split(argv, ' ');
	if (!**cmd_arr || !*cmd_arr[0])
		ft_putstr_fd("error\ncommand not found\n", 2);
	else
	{
		if (access(*cmd_arr[0], F_OK) == 0)
		{
			*cmd_path = ft_strdup(*cmd_arr[0]);
			if (!*cmd_path)
				ft_putstr_fd("error\npath couldn't be created\n", 2);
		}
		else
			check_full_path_in_envp(cmd_arr, cmd_path, envp);
	}
}

void	check_full_path_in_envp(char ***cmd_arr, char **cmd_path, char **envp)
{
	char	**path_envp;

	path_envp = search_path(envp);
	if (!path_envp || !path_envp[0])
	{
		ft_putstr_fd("error\npath doesn't exist in envp\n", 2);
		return ;
	}
	check_path_cmd_validity(path_envp, cmd_arr, cmd_path);
	free_arr(path_envp);
	return ;
}

char	**search_path(char **envp)
{
	int		i;
	char	**path;

	path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_split(ft_strchr(envp[i], '/'), ':');
			return (path);
		}
		else
			i++;
	}
	return (path);
}

void	check_path_cmd_validity(char **path, char ***cmd_arr, char **cmd_path)
{
	char	*path_with_cmd;

	while (*path)
	{
		path_with_cmd = NULL;
		path_with_cmd = ft_strjoin(*path, "/");
		path_with_cmd = ft_strjoin_freed(path_with_cmd, *cmd_arr[0]);
		if (!path_with_cmd || !path_with_cmd[0])
			ft_putstr_fd("error\nat least one path couldn'be checked \
			in envp\n", 2);
		if (access(path_with_cmd, F_OK) == 0)
		{
			*cmd_path = ft_strdup(path_with_cmd);
			if (!cmd_path)
				ft_putstr_fd("error\nat least one path couldn'be checked\
				in envp\n", 2);
			free (path_with_cmd);
			return ;
		}
		free (path_with_cmd);
		path ++;
	}
	ft_putstr_fd("error\ncommand not found\n", 2);
	return ;
}*/