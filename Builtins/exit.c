/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:57:29 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/09 14:09:50 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>
#include <unistd.h>

static void	message_exit(t_exec_struct *exec_struct, char **envp_arr)
{
	int	code;

	code = exec_struct->command_line->previous_exit_code;
	free_envp_struct(&exec_struct->envp_struct);
	free_all_command_line(&exec_struct->command_line);
	free_all_exec_struct(&exec_struct);
	free_arr(envp_arr);
	clear_history();
	exit(code);
}

static void	message_error(char *str,
	t_exec_struct *exec_struct, char **envp_arr)
{
	write(2, "exit\n", 5);
	write(2, "bash: exit: ", 12);
	ft_putstr_fd(str, 2);
	write(2, ": numeric argument required\n", 28);
	exec_struct->command_line->previous_exit_code = 2;
	message_exit(exec_struct, envp_arr);
}

static int	arguments_is_valid(char *nptr,
	unsigned long long nbr, int sign, int i)
{
	if ((sign == 1 && nbr > LLONG_MAX)
		|| (sign == -1 && nbr > (unsigned long long)LLONG_MAX + 1))
		return (1);
	if (nptr[i] != '\0')
		return (1);
	if ((nptr[0] == '-' || nptr[0] == '+') && nptr[1] == '\0')
		return (1);
	return (0);
}

static void	calculint(char *nptr, int i,
	t_exec_struct *exec_struct, char **envp_arr)
{
	int	countnumber;

	countnumber = 0;
	while (nptr[i] == '0')
		i++;
	while (nptr[i])
	{
		i++;
		countnumber++;
	}
	if (countnumber > 19)
		message_error(nptr, exec_struct, envp_arr);
}

static int	ft_aatoi(char *nptr, t_exec_struct *exec_struct, char **envp_arr)
{
	unsigned long long	nbr;
	int					sign;
	int					i;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	calculint(nptr, i, exec_struct, envp_arr);
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nbr = 10 * nbr + (nptr[i] - 48);
		i++;
	}
	if (arguments_is_valid(nptr, nbr, sign, i))
		message_error(nptr, exec_struct, envp_arr);
	if (nbr > 255)
		nbr = nbr % 256;
	return (nbr * sign);
}

void	exit_builting(t_exec_struct *exec_struct, t_exec_argument *exec_arguments, char **envp_arr)
{
	size_t	len;

	len = ft_lst_size9(exec_arguments);
	if (len == 1)
	{
		write(2, "exit\n", 5);
		message_exit(exec_struct, envp_arr);
	}
	exec_struct->command_line->previous_exit_code = ft_aatoi(exec_arguments->next->argument, exec_struct, envp_arr);
	write(2, "exit\n", 5);
	if (len > 2)
	{
		write(2, "bash: exit: too many arguments\n", 31);
		exec_struct->command_line->current_exit_code = 1;
		return ;
	}
	message_exit(exec_struct, envp_arr);
}
