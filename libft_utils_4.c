/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/09 15:41:08 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/libft_utils.h"
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
	while (str && *str && (ft_isspace(*str) == 0))
		str++;
	return (str);
}

int	ft_isspace(int c)
{
	if (((c >= 9) && (c <= 13)) || c == 32)
		return (0);
	return (1);
}
