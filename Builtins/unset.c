/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:11 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/11 06:31:32 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	t_exec_argument	*arguments;
	t_envp_struct	*current;
	t_envp_struct	*previous;

	arguments = exec_arguments->next;
	if (arguments && arguments->argument[0] == '-')
		exec_struct->command_line->current_exit_code = 2;
	while (arguments)
	{
		current = exec_struct->envp_struct;
		previous = exec_struct->envp_struct;
		while (current)
		{
			if (!strcmp(arguments->argument, current->name))
			{
				if (current == previous)
					exec_struct->envp_struct = current->next;
				else
					previous->next = current->next;
				free(current->name);
				if (current->value)
					free(current->value);
				free(current);
				break ;
			}
			if (current != previous)
				previous = previous->next;
			current = current->next;
		}
		arguments = arguments->next;
	}
}
