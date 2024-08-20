/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:51 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:31:59 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len_and_extract_after_first_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = ft_strcspn(&str[1], "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator + 1);//malloc à protéger
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator + 1;
	return (len);
}

static char	*get_variable_content_in_envp(char *variable, \
t_envp_struct *envp_struct)
{
	t_envp_struct	*cursor;
	char			*result;

	cursor = envp_struct;
	result = NULL;
	while (cursor)
	{
		if (ft_strcmp(variable, cursor->name) == 0)
		{
			result = ft_strdup(cursor->value);
			return (result);
		}
		cursor = cursor->next;
	}
	return (result);
}

static int	expand_variables_when_dollar_first(char \
*remaining_line, char **result, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*tmp;

	len_to_cut = 0;
	if ((remaining_line[1] && ft_isspace(remaining_line[1]) == false))
	{
		if (remaining_line[1] == '\"' || remaining_line[1] == '\'')
			*result = ft_strdup("");
		else
		{
			len_to_cut = (int)strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
			tmp = ft_substr(&remaining_line[1], 0, len_to_cut);//protect
			*result = get_variable_content_in_envp(tmp, envp_struct);
			tmp = free_and_null(tmp);
			if (!*result)
				*result = ft_strdup("");
		}
	}
	else
		*result = ft_strdup("$");
	return (len_to_cut);
}

char	*expand_variables(char **remaining_line, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		len_to_cut = expand_variables_when_dollar_first(remaining_line[0], \
		&result, envp_struct);
		*remaining_line += len_to_cut + 1;
	}
	else
	{
		len_to_cut = ft_strcspn(remaining_line[0], "$\0");
		result = ft_substr(remaining_line[0], 0, len_to_cut);//malloc à protéger
		*remaining_line += len_to_cut;
	}
	return (result);
}
