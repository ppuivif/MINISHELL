/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:54:36 by drabarza          #+#    #+#             */
/*   Updated: 2024/06/27 15:43:32 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_is_builtin(t_exec_argument *exec_arguments)
{
	int	var;
	
	var = 0;
	if (!ft_strcmp(exec_arguments->argument, "echo"))
		var = echo(exec_arguments);
	//if (!ft_strcmp(exec_arguments->argument, "cd"))
	//	var = cd(exec_arguments);
	if (!ft_strcmp(exec_arguments->argument, "pwd"))
		var = pwd();
	/*if (!ft_strcmp(exec_arguments->argument, "export"))
		var = export(exec_arguments);
	if (!ft_strcmp(exec_arguments->argument, "unset"))
		var = unset(exec_arguments);
	if (!ft_strcmp(exec_arguments->argument, "env"))
		var = env(exec_arguments);
	if (!ft_strcmp(exec_arguments->argument, "exit"))
		var = exit(exec_arguments);*/
		return (var);
}