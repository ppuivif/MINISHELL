/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:57:29 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 10:03:00 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	message_exit(t_exec_struct *exec_struct, char **envp_arr)
{
	int	code;

	code = exec_struct->command_line->previous_exit_code;
	free_envp_struct(&exec_struct->envp_struct);
	free_all_command_line(&exec_struct->command_line);
	free_all_exec_struct(&exec_struct);
	free_arr(envp_arr);
	rl_clear_history();
	exit(code);
}

void	message_error(char *str, \
t_exec_struct *exec_struct, char **envp_arr)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exec_struct->command_line->previous_exit_code = 2;
	message_exit(exec_struct, envp_arr);
}

void	exit_builting(t_exec_struct *exec_struct, \
t_exec_argument *exec_arguments, char **envp_arr)
{
	size_t	len;

	len = ft_lst_size9(exec_arguments);
	if (len == 1 && ft_lst_size7(exec_struct->exec_substrings) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		message_exit(exec_struct, envp_arr);
	}
	exec_struct->command_line->previous_exit_code = \
	ft_aatoi(exec_arguments->next->argument, exec_struct, envp_arr);
	ft_putstr_fd("exit\n", 2);
	if (len > 2)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		exec_struct->command_line->current_exit_code = 1;
		return ;
	}
	message_exit(exec_struct, envp_arr);
}
