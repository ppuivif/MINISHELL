/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:49:45 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_content_heredoc_when_dollar_first(char *str, \
char **tmp, t_envp_struct *envp_struct, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[1] != '\"' && str[1] != '\'' && (str[1]) != 0)
	{
		len += get_len_and_extract_after_first_dollar(str, tmp);
		expand_string_after_dollar1(tmp, envp_struct, command_line);
	}
	else
		len += get_len_and_extract_until_next_separator_dollar_excluded \
		(str, tmp);
	return (len);
}

void	expand_content_when_heredoc(char **str, t_envp_struct *envp_struct, \
t_command_line **command_line, bool flag_for_expand)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			if (flag_for_expand == true)
				i += expand_content_heredoc_when_dollar_first \
				(&str[0][i], &tmp, envp_struct, command_line);
			else
			{
				i += get_len_and_extract_until_next_dollar_first_dollar_excluded(&str[0][i], &tmp);
			}
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp);
		if (!result)
		{
			result = ft_strdup_freed(tmp);
			tmp = NULL;
		}
		else
		{
			result = ft_strjoin_freed(result, tmp);
			tmp = free_and_null(tmp);
		}
	}
	free(*str);
	*str = ft_strdup_freed(result);
}
