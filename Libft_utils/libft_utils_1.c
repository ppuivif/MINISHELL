/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:59:46 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 12:04:26 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n)
	{
		if ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
			i++;
		else
			return (str1[i] - str2[i]);
	}
	return (0);
}

int	ft_strcspn(char *remaining_line, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (remaining_line[i])
	{
		j = 0;
		while (str[j])
		{
			if (remaining_line[i] == str[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char	*skip_first_whitespaces(char *str)
{
	while (str && *str && (ft_isspace(*str) == true))
		str++;
	return (str);
}
