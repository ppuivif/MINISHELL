/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:20:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 20:19:03 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_env(t_exec_struct *exec_struct, \
t_exec_argument *exec_arguments)
{
	if (exec_arguments->next)
	{
		if ((exec_arguments->next->argument[0] == '-') && \
		ft_strcmp(exec_arguments->next->argument, "--"))
		{
			if (!ft_strcmp(exec_arguments->next->argument, "-"))
				return (1);
			ft_putstr_fd("env: invalid option -- '", 2);
			write(2, &exec_arguments->next->argument[1], 1);
			ft_putstr_fd("'\n", 2);
			exec_struct->command_line->current_exit_code = 125;
			return (1);
		}
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(exec_arguments->next->argument, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		exec_struct->command_line->current_exit_code = 127;
		return (1);
	}
	return (0);
}

void	env(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	if (error_env(exec_struct, exec_arguments))
		return ;
	while (env)
	{
		if (env->name && env->equal == 1)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}
