/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:57:29 by drabarza          #+#    #+#             */
/*   Updated: 2024/06/27 14:45:30 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit(t_exec_argument *exec_arguments)
{
	int	i;

	if (!exec_arguments->argument[1])
		return (1);
	i = 0;
	while (exec_arguments->argument[1])
	{
		if (exec_arguments->argument[1][i] < '0' || exec_arguments->argument[1][i] < '9')
			{
				write(2, "bash: exit: ", 12);
				
				write(2, ": numeric argument required", 27);
			}
		i++;
	}
}

int	main(void)
{
}