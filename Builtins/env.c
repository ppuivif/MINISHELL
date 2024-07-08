/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:20:53 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/08 21:32:48 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_exec_struct *exec_struct)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		printf("%s\n", env->name);//to modifiy with ft_strjoin(name,=,value)
		env = env->next;
	}
	return (1);
}
