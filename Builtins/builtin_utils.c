/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:54:36 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/17 18:41:15 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtin(t_exec_struct *exec_struct, \
t_exec_substring *substring, char **envp_arr)
{
	if (!ft_strcmp(substring->exec_arguments->argument, "echo"))
		echo(substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "cd"))
		cd(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "pwd"))
		pwd();
	if (!ft_strcmp(substring->exec_arguments->argument, "export"))
		export(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "unset"))
		unset(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "env"))
		env(exec_struct);
	if (!ft_strcmp(substring->exec_arguments->argument, "exit"))
		exit_builting(exec_struct, substring->exec_arguments, envp_arr);
}

int	check_is_builtin(t_exec_argument *exec_arguments)
{
	exec_arguments->is_builtin = 0;
	if (!ft_strcmp(exec_arguments->argument, "echo"))
		exec_arguments->is_builtin = 1;
	if (!ft_strcmp(exec_arguments->argument, "cd"))
		exec_arguments->is_builtin = 2;
	if (!ft_strcmp(exec_arguments->argument, "pwd"))
		exec_arguments->is_builtin = 1;
	if (!ft_strcmp(exec_arguments->argument, "export"))
		exec_arguments->is_builtin = 2;
	if (!ft_strcmp(exec_arguments->argument, "unset"))
		exec_arguments->is_builtin = 2;
	if (!ft_strcmp(exec_arguments->argument, "env"))
		exec_arguments->is_builtin = 1;
	if (!ft_strcmp(exec_arguments->argument, "exit"))
		exec_arguments->is_builtin = 2;
	return (exec_arguments->is_builtin);
}
