/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:54:36 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/03 17:53:57 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_option(t_exec_struct *exec_struct, \
t_exec_argument *exec_arguments, char *str)
{
	if (exec_arguments->next)
	{
		if (exec_arguments->next->argument[0] == '-' && \
		(ft_strcmp(exec_arguments->next->argument, "-") && \
		ft_strcmp(exec_arguments->next->argument, "--")))
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": -", 2);
			write(2, &exec_arguments->next->argument[1], 1);
			ft_putstr_fd(": invalid option\n", 2);
			exec_struct->command_line->current_exit_code = 2;
			return (1);
		}
	}
	return (0);
}

void	exec_builtin(t_exec_struct *exec_struct, \
t_exec_substring *substring, char **envp_arr)
{
	if (!ft_strcmp(substring->exec_arguments->argument, "echo"))
		echo(substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "cd"))
		cd(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "pwd"))
		pwd(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "export"))
		export(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "unset"))
		unset(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "env"))
		env(exec_struct, substring->exec_arguments);
	if (!ft_strcmp(substring->exec_arguments->argument, "exit"))
		exit_builting(exec_struct, substring->exec_arguments, envp_arr);
}

int	check_is_builtin(t_exec_argument *exec_arguments)
{
	exec_arguments->is_builtin = ISNOT_BUILTIN;
	if (!ft_strcmp(exec_arguments->argument, "echo"))
		exec_arguments->is_builtin = IOPUT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "cd"))
		exec_arguments->is_builtin = IOPUT_NOT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "pwd"))
		exec_arguments->is_builtin = IOPUT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "export"))
		exec_arguments->is_builtin = IOPUT_NOT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "unset"))
		exec_arguments->is_builtin = IOPUT_NOT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "env"))
		exec_arguments->is_builtin = IOPUT_ACCEPTED;
	if (!ft_strcmp(exec_arguments->argument, "exit"))
		exec_arguments->is_builtin = IOPUT_NOT_ACCEPTED;
	return (exec_arguments->is_builtin);
}
