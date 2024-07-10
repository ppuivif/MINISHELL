/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:20:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/09 14:09:48 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_exec_struct *exec_struct)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		if (env->name || env->equal == 1)
		{
			printf("%s=", env->name);
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}
