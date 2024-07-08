/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:16 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/08 21:31:41 by ppuivif          ###   ########.fr       */
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

int	cd(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	char	*home;
	char	*old;
	size_t	size;

	size = ft_lst_size9(exec_arguments);
	if (size > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (size == 1 || !ft_strcmp(exec_arguments->next->argument, "--"))
	{
		home = strdup(search_home(exec_struct));
		if (!home)
		{
			printf("bash: cd: HOME not set\n");
			exec_struct->command_line->current_exit_code = 1;
		}
		else if (chdir(home) == -1)
		{
			printf(": Permission denied\n");
			exec_struct->command_line->current_exit_code = 1;
		}
		free(home);
		return (1);
	}
	if (exec_arguments->next->argument[0] == '-')
	{
		printf("%s\n", search_or_replace_oldpwd(exec_struct, NULL));
		return (1);
	}
	old = getcwd(NULL, 0);
	if (chdir(exec_arguments->next->argument) == -1)
	{
		if (errno == EACCES)
		{
			ft_putstr_fd(exec_arguments->next->argument, 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		else if (access(exec_arguments->next->argument, F_OK) == 0)//F_OK to verify if file exists, X_OK to verify if the file is executable
		{
			ft_putstr_fd(exec_arguments->next->argument, 2);
			ft_putstr_fd("cd: Makefile: Not a directory\n", 2);
		}
		else
		{
			ft_putstr_fd(exec_arguments->next->argument, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		exec_struct->command_line->current_exit_code = 1;
		free(old);
		return (1);
	}
	search_or_replace_oldpwd(exec_struct, old);
	free(old);
	return (1);
}
