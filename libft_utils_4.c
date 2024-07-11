/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/07/11 06:43:14 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_utils.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -1 * n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	c = n % 10 + '0';
	write (fd, &c, 1);
}

char	*skip_first_whitespaces(char *str)
{
	while (str && *str && (ft_isspace(*str) == true))
		str++;
	return (str);
}

bool	ft_isspace(int c)
{
	if (((c >= 9) && (c <= 13)) || c == 32)
		return (true);
	return (false);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] < s2[i] || s1[i] > s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}
