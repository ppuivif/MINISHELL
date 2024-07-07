/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:16 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/07 16:23:30 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_home(t_exec_struct *exec_struct)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		if (!strncmp(env->content, "HOME", 4))
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
		if (!strncmp(env->content, "OLDPWD", 6))
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

int	cd(t_exec_struct *exec_struct)
{
	char	*home;
	char	*old;
	size_t	size;

	size = ft_lst_size9(exec_struct->exec_substrings->exec_arguments);
	if (size > 2)
	{
		write(2, "bash: cd: too many arguments\n", 29);
		return (1);
	}
	if (size == 1 || !ft_strcmp \
		(exec_struct->exec_substrings->exec_arguments->next->argument, "--"))
	{
		home = strdup(search_home(exec_struct));
		if (!home)
			printf("bash: cd: HOME not set\n");
		else if (chdir(home) == -1)
			printf("Error\n");
		free(home);
		return (1);
	}
	if (exec_struct->exec_substrings->exec_arguments->next->argument[0] == '-')
	{
		printf("%s\n", search_or_replace_oldpwd(exec_struct, NULL));
		return (1);
	}
	old = getcwd(NULL, 0);
	if (chdir(exec_struct->exec_substrings \
		->exec_arguments->next->argument) == -1)
	{
		write(2, "cd: no such file or directory: ", 31);
		ft_putstr_fd(exec_struct->exec_substrings->exec_arguments->next->argument, 2);
		write(2, "\n", 1);
		free(old);
		return (1);
	}
	search_or_replace_oldpwd(exec_struct, old);
	free(old);
	return (1);
}
