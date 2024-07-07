/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:11 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/07 09:47:13 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_exec_struct *exec_struct)
{
	(void) exec_struct;
	/*t_exec_argument *arguments;
	t_envp_struct	*env;
	t_envp_struct	*new_env;

	arguments = exec_struct->exec_substrings->exec_arguments;
	while (arguments)
	{
		env = exec_struct->envp_struct;
		while (env)
		{
			if (!strcmp(exec_struct->exec_substrings \
				->exec_arguments->next->argument, env->name))
			{
				if (env)
					new_env = env->next;
				else
					exec_struct->envp_struct = env->next;
				free(env->content);
				free(env->name);
				free(env->value);
				free(env);
			}
			new_env = env;
			env = env->next;
		}
		arguments = arguments->next;
	}*/
	return (1);
}
