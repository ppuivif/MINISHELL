/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/23 10:54:38 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_content_heredoc_when_dollar_first(char *str, \
char **tmp, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[1] != '\"' && str[1] != '\'' && (str[1]) != 0)
	{
		len += get_len_and_extract_after_first_dollar(str, tmp, command_line);
		expand_string_after_dollar1(tmp, command_line);
	}
	else
		len += get_len_and_extract_until_next_separator_dollar_excluded \
		(str, tmp);
	return (len);
}

void	expand_content_when_heredoc(char **str, t_command_line **command_line, \
bool flag_for_expand)
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
				(&str[0][i], &tmp, command_line);
			else
			{
				i += get_len_and_extract_until_next_dollar_first_dollar_excluded(&str[0][i], &tmp);
			}
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp, \
			command_line);
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

void	add_to_definitive_content(char **definitive_content, char *extracted_line, \
t_command_line **command_line, char *str)
{
	if (!*definitive_content)
		*definitive_content = ft_strdup(extracted_line);
	else
		*definitive_content = \
		ft_strjoin_freed(*definitive_content, extracted_line);
	extracted_line = free_and_null(extracted_line);
	if (!*definitive_content)
	{
		free(str);
		error_allocation_command_line_and_exit(command_line);
	}
}

void	check_ambiguous_redirection(char **extracted_line, \
t_native_redirection **n_redirection)
{
	size_t	len;
	size_t	len_to_separator;

	len = ft_strlen(*extracted_line);
	len_to_separator = ft_strcspn(*extracted_line, " \t\n\v\f\r\0");
	if (len == 0 || len_to_separator < len)
		(*n_redirection)->t_redirection = REDIRECTION_AMBIGUOUS;
}
