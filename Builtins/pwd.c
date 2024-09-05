/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:30:07 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 21:47:07 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	char	str[PATH_MAX];

	if (error_option(exec_struct, exec_arguments, "pwd"))
		return ;
	if (getcwd(str, PATH_MAX))
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd("An error as detected\n", 2);
	}
}
