/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:58:37 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 16:01:20 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

bool	ft_isspace(int c)
{
	if (((c >= 9) && (c <= 13)) || c == 32)
		return (true);
	return (false);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = nmemb * size;
	if (!size || !nmemb)
		return (malloc(1));
	if (j > 4294967295 || (size > 65535 && nmemb > 65535))
		return (NULL);
	str = (char *)malloc(j);
	if (str)
	{
		while (i < j)
		{
			str[i] = '\0';
			i++;
		}
		return ((void *) str);
	}
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	str = malloc((len + 1) * sizeof(char));
	if (str)
	{
		while (i < (unsigned int)len)
		{
			str[i] = s[start + i];
			i++;
		}
		str[i] = 0;
		return (str);
	}
	return (NULL);
}
