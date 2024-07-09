/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:29:44 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/08 18:09:11 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

static int	check_argument(t_exec_argument *exec_arguments)
{
	int		i;

	i = 1;
	if (exec_arguments->argument[0] != '-')
		return (0);
	while (exec_arguments->argument[i])
	{
		if (exec_arguments->argument[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

static void	ft_putstrr(t_exec_argument *exec_arguments)
{
	int	i;

	i = 0;
	if (exec_arguments->argument)
	{
		while (exec_arguments->argument[i])
		{
			write(1, &exec_arguments->argument[i], 1);
			i++;
		}
	}
}

int	echo(t_exec_argument *exec_arguments)
{
	t_exec_argument	*arguments;
	int				n;

	arguments = exec_arguments;
	n = 1;
	if (!arguments->next)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (arguments && check_argument(arguments->next))
	{
		arguments = arguments->next;
		n = 0;
	}
	while (arguments->next)
	{
		ft_putstrr(arguments->next);
		if (arguments->next->next)
			write(1, " ", 1);
		arguments = arguments->next;
	}
	if (n == 1)
		write(1, "\n", 1);
	return (1);
}
