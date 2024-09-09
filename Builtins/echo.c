/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:29:44 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/09 15:28:20 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	echo(t_exec_argument *exec_arguments, int fd)
{
	t_exec_argument	*arguments;
	int				n;

	arguments = exec_arguments->next;
	n = 1;
	if (!arguments)
	{
		ft_putstr_fd("\n", fd);
		return ;
	}
	while (arguments && check_argument(arguments))
	{
		arguments = arguments->next;
		n = 0;
	}
	while (arguments)
	{
		ft_putstr_fd(arguments->argument, fd);
		if (arguments->next)
			ft_putstr_fd(" ", fd);
		arguments = arguments->next;
	}
	if (n == 1)
		ft_putstr_fd("\n", fd);
}
