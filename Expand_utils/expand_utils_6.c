/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/27 09:34:38 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_string_between_single_quotes(char **str, \
t_command_line **command_line)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = NULL;
	result = NULL;
	while (*str && str[0][i])
	{
		if (str[0][i] == '$')
		{
			i += get_len_and_extract_after_first_dollar(&str[0][i], &tmp, \
			command_line);
			expand_string_after_dollar1(&tmp, command_line);
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp, \
			command_line);
		add_to_definitive_content(&result, tmp, command_line, NULL);
	}
	free(*str);
	*str = ft_strdup_freed(result);
	if (!(*str))
		error_allocation_command_line_and_exit(command_line);
}

static int	expand_content_of_redirections_when_dollar_first(char *str, \
char **tmp, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[1] == '\"' || str[1] == '\'')
	{
		*tmp = ft_strdup("$");
		if (!(*tmp))
			error_allocation_command_line_and_exit(command_line);
		len = 1;
	}
	else
	{
		len = get_len_and_extract_after_first_dollar(str, tmp, command_line);
		expand_string_after_dollar1(tmp, command_line);
	}
	return (len);
}

int	expand_content_when_dollar_not_first(char *str, \
char **tmp, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[0] == '\"')
		len += get_len_and_extract_between_quotes(str, tmp, \
		command_line, '\"');
	else if (str[0] == '\'')
	{
		len += get_len_and_extract_with_single_quotes(str, tmp, command_line);
		if (strcspn(*tmp, "$") < ft_strlen(*tmp))
			expand_string_between_single_quotes(tmp, command_line);
	}
	else if (ft_isspace(str[0]) == true)
		len += get_len_and_extract_until_next_quote_or_dollar(str, tmp, \
		command_line);
	else
		len += get_len_and_extract_until_next_separator(str, tmp, \
		command_line);
	return (len);
}

static int	expand_content_when_dollar_first(char *str, \
char **tmp, t_command_line **command_line)
{
	int	i;	
	int	len;

	i = 0;
	len = handle_special_characters_after_dollar(str, \
	tmp, command_line, false);
	if (len == 0)
		i = expand_content_of_redirections_when_dollar_first \
		(str, tmp, command_line);
	else
		i = len;
	return (i);
}

void	complete_expand_content_of_redirections(char **str, \
t_command_line **command_line)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = NULL;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
			i += expand_content_when_dollar_first \
			(&str[0][i], &tmp, command_line);
		else
			i += expand_content_when_dollar_not_first \
			(&str[0][i], &tmp, command_line);
		add_to_definitive_content(&result, tmp, command_line, NULL);
	}
	free(*str);
	*str = ft_strdup_freed(result);
	if (!str)
		error_allocation_command_line_and_exit(command_line);
}
