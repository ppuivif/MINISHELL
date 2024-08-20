/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:45:47 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	complete_expand_content_of_arguments(char **extracted_line, \
t_command_line **command_line, bool flag_keep_dollar)
{
	int		i;
	char	*tmp;
	char	*result;
	size_t	len;

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
			if (len != 0)
				i += (int)len;
			else
			{
/*				i += expand_content_of_arguments_when_dollar_first \
				(&extracted_line[0][i], &tmp, command_line->envp_struct);*/
				//to complete whith case of sapces in variable value
				i += get_len_and_extract_after_first_dollar \
				(&extracted_line[0][i], &tmp);
				expand_string_after_dollar1(&tmp, \
				(*command_line)->envp_struct, command_line);
			}
		}
		else
			i += expand_content_when_dollar_not_first (&extracted_line[0][i], \
			&tmp, (*command_line)->envp_struct, command_line);
		if (!result)
		{
			result = ft_strdup_freed(tmp);//malloc à protéger
			tmp = NULL;
		}
		else
		{
			result = ft_strjoin_freed(result, tmp);//malloc à protéger
			tmp = free_and_null(tmp);
		}
	}
	free(*extracted_line);
	*extracted_line = ft_strdup_freed(result);//malloc à protéger
}
