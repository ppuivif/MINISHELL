/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 16:01:36 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

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

int	ft_atoi(const char *nptr)
{
	int	i;
	int	j;
	int	nbr;

	i = 0;
	j = 1;
	nbr = 0;
	while (nptr[i] != '\0' && (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14)))
		i++;
	if (nptr[i] != '\0' && (nptr[i] == 45 || nptr[i] == 43))
	{
		if (nptr[i] == 45)
			j = j * -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] > 47 && nptr[i] < 58)
	{
		nbr = (nbr * 10) + (nptr[i] - 48);
		i++;
	}
	return (nbr * j);
}
