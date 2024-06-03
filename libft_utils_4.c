/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/06/03 12:35:25 by ppuivif          ###   ########.fr       */
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

static int	ft_lenght_param(long int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_sign(int n)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
	}
	return (sign);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	nb;
	int			sign;

	nb = n;
	sign = ft_sign(nb);
	if (sign == 1)
		nb *= -1;
	i = ft_lenght_param(nb) + sign;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	if (sign == 1)
		str[0] = '-';
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[i - 1] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (str);
}