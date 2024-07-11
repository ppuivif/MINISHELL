/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:09:15 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/11 09:14:26 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	skip_whitespaces(char *nptr, int *i)
{
	while ((nptr[*i] >= '\t' && nptr[*i] <= '\r') || nptr[*i] == ' ')
		(*i)++;
}

int	ft_aatoi(char *nptr, t_exec_struct *exec_struct, char **envp_arr)
{
	unsigned long long	nbr;
	int					sign;
	int					i;

	nbr = 0;
	sign = 1;
	i = 0;
	skip_whitespaces(nptr, &i);
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
