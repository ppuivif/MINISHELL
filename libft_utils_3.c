/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:27:17 by ppuivif           #+#    #+#             */
/*   Updated: 2024/07/11 11:51:16 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_utils.h"

void	*free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free (arr[i]);
			arr[i] = NULL;
			i++;
		}
		free (arr);
		arr = NULL;
	}
	return (arr);
}

static int	ft_count_words(char const *s, char c)

{
	int		count;
	size_t	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_start_str(char const *s, char c, int count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (count == 1)
		return (0);
	if (!s)
		return (0);
	while (j < count - 1)
	{
		if (s[i] == '\0')
			break ;
		if (s[i + 1] != '\0' && s[i] == c && s[i + 1] != c)
		{
			j++;
			i++;
		}
		i++;
	}
	return (i - 1);
}

static int	ft_len_str(char const *s, char c, int start)
{
	int	i;

	i = start;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i - start);
}

char	**ft_split(char const *s, char c)
{
	int		start;
	int		len;
	int		i;
	char	**tab;

	if (s == NULL)
		return (NULL);
	tab = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < ft_count_words(s, c) && *s)
	{
		while (*s == c && *s)
			s++;
		start = ft_start_str(s, c, i + 1);
		len = ft_len_str(s, c, start);
		tab[i] = ft_substr(s, start, len);
		if (!tab[i])
			return (free_arr(tab));
		i++;
	}
	return (tab);
}
