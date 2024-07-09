/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:16 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/09 03:40:47 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_home(t_exec_struct *exec_struct)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		if (!strncmp(env->name, "HOME", 4))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*search_or_replace_oldpwd(t_exec_struct *exec_struct, char *str)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		if (!strncmp(env->name, "OLDPWD", 6))
		{
			if (!str)
				return (env->value);
			free(env->value);
			env->value = ft_strdup(str);
			return (NULL);
		}
		env = env->next;
	}
	return (NULL);
}

static void	check_error(t_exec_struct *exec_struct, char *argument)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (access(argument, F_OK) == 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(argument, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	exec_struct->command_line->current_exit_code = 1;
}

void	cd(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	char	*home;
	char	*old;
	size_t	size;

	size = ft_lst_size9(exec_arguments);
	if (size > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		exec_struct->command_line->current_exit_code = 1;
		return ;
	}
	if (size == 1 || !ft_strcmp(exec_arguments->next->argument, "--") || !ft_strcmp(exec_arguments->next->argument, "~"))
	{
		home = strdup(search_home(exec_struct));
		if (!home)
		{
			printf("bash: cd: HOME not set\n");
			exec_struct->command_line->current_exit_code = 1;
		}
		else if (chdir(home) == -1)
		{
			check_error(exec_struct, home);
		}
		free(home);
		return ;
	}
	if (exec_arguments->next->argument[0] == '-')
	{
		printf("%s\n", search_or_replace_oldpwd(exec_struct, NULL));
		return ;
	}
	old = getcwd(NULL, 0);
	if (chdir(exec_arguments->next->argument) == -1)
	{
		check_error(exec_struct, exec_arguments->next->argument);
		free(old);
		return ;
	}
	search_or_replace_oldpwd(exec_struct, old);
	free(old);
}
