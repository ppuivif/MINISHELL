/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:30:07 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/09 15:36:33 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_exec_struct *exec_struct, t_exec_argument *exec_arguments, int fd)
{
	char	str[PATH_MAX];

	if (error_option(exec_struct, exec_arguments, "pwd"))
		return ;
	if (getcwd(str, PATH_MAX))
	{
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd("An error as detected\n", 2);
	}
}
