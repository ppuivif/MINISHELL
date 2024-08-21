/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 10:21:17 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_expand_content_of_arguments(char **extracted_line, \
t_command_line **command_line, bool flag_keep_dollar)
{
	int		i;
	char	*tmp;
	char	*result;
	int	len;

	i = 0;
	tmp = NULL;
	result = NULL;
	len = 0;
	while (extracted_line[0][i])
	{
		if (extracted_line[0][i] == '$')
		{
			len = handle_special_characters_after_dollar(&extracted_line[0][i], \
			&tmp, command_line, flag_keep_dollar);
			if (len == -1)
				error_allocation_command_line_and_exit(command_line);
			if (len == 0)
			{
/*				i += expand_content_of_arguments_when_dollar_first \
				(&extracted_line[0][i], &tmp, command_line->envp_struct);*/
				//to complete whith case of sapces in variable value
				i += get_len_and_extract_after_first_dollar \
				(&extracted_line[0][i], &tmp, command_line);
				expand_string_after_dollar1(&tmp, command_line);
			}
			else
				i += (int)len;
		}
		else
			i += expand_content_when_dollar_not_first(&extracted_line[0][i], \
			&tmp, command_line);
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
		if (!result)
			error_allocation_command_line_and_exit(command_line);
	}
	free(*extracted_line);
	*extracted_line = ft_strdup_freed(result);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
		
}
