/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:16 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/06 17:09:13 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_home(t_exec_struct *exec_struct)
{
	while (exec_struct->envp_struct->next)
	{
		printf("%s\n", exec_struct->envp_struct->content);
		if (!strncmp(exec_struct->envp_struct->content, "HOME", 4))
		{
			return (exec_struct->envp_struct->content);
		}
		exec_struct->envp_struct = exec_struct->envp_struct->next;
	}
	return (NULL);
}

int	cd(t_exec_struct *exec_struct)
{
	char	*home;

    if (!exec_struct->exec_substrings->exec_arguments->next)
	{
		home = strdup(search_home(exec_struct));
        if (home)
			printf("%s\n", home);
		else
			printf("Error\n");
		return (1);
	}
	return (1);
}