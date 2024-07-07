/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:54:36 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/07 13:02:48 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	exec_builtin(t_exec_struct *exec_struct, char **envp_arr)
{
	int	var;
	
	var = 0;
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "echo"))
		var = echo(exec_struct->exec_substrings->exec_arguments);
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "cd"))
		var = cd(exec_struct);
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "pwd"))
		var = pwd();
	//if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "export"))
	//	var = export(exec_struct->exec_substrings->exec_arguments);
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "unset"))
		var = unset(exec_struct);
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "env"))
		var = env(exec_struct);
	if (!ft_strcmp(exec_struct->exec_substrings->exec_arguments->argument, "exit"))
		var = exit_builting(exec_struct, envp_arr);
	return (var);
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