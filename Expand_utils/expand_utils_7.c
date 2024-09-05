/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 09:44:31 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_arg_content_when_dollar_first(char *extracted_line, \
char **tmp, t_command_line **command_line, bool flag_keep_dollar)
{
	int	len;

	len = handle_special_characters_after_dollar(extracted_line, \
	tmp, command_line, flag_keep_dollar);
	if (len == 0)
	{
		len += get_len_and_extract_after_first_dollar \
		(extracted_line, tmp, command_line);
		expand_string_after_dollar1(tmp, command_line);
	}
	return (len);
}

void	complete_expand_content_of_arguments(char **extracted_line, \
t_command_line **command_line, bool flag_keep_dollar)
{
	int		i;
	char	*tmp;
	char	*definitive_content;

	i = 0;
	tmp = NULL;
	definitive_content = NULL;
	while (extracted_line[0][i])
	{
		if (extracted_line[0][i] == '$')
			i += expand_arg_content_when_dollar_first(&extracted_line[0][i], \
			&tmp, command_line, flag_keep_dollar);
		else
			i += expand_content_when_dollar_not_first(&extracted_line[0][i], \
			&tmp, command_line);
		add_to_definitive_content(&definitive_content, tmp, \
		command_line, NULL);
	}
	free(*extracted_line);
	*extracted_line = ft_strdup_freed(definitive_content);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
}
