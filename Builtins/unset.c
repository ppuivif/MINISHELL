/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:11 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/11 11:54:59 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_remove(t_exec_struct *exec_struct, t_envp_struct *current, \
t_envp_struct *previous)
{
	if (current == previous)
		exec_struct->envp_struct = current->next;
	else
		previous->next = current->next;
	free(current->name);
	if (current->value)
		free(current->value);
	free(current);
}

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
				unset_remove(exec_struct, current, previous);
				break ;
			}
			if (current != previous)
				previous = previous->next;
			current = current->next;
		}
		arguments = arguments->next;
	}
}
