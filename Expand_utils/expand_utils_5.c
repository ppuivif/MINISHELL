/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/23 16:13:01 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_string_after_dollar1(char **str, t_command_line **command_line)
{
	char	*remaining_line;
	char	*variable;
	char	*result;
	int		len;

	result = NULL;
	remaining_line = *str;
	len = 0;
	while (remaining_line && remaining_line[0])
	{
		len = handle_special_characters_after_dollar(remaining_line, \
		&variable, command_line, 1);
		if (len == 0)
			variable = expand_variables(&remaining_line, command_line);
		else
			remaining_line += len;

		add_to_definitive_content(&result, variable, command_line, NULL);
	}
	*str = free_and_null (*str);
	*str = ft_strdup_freed(result);
	if (!str)
		error_allocation_command_line_and_exit(command_line);
}

void	expand_string_after_dollar2(char *str, \
t_expanded_argument **exp_arguments, char **definitive_content, \
t_command_line **command_line)
{
	char	*variable;
	char	*extracted_argument;
	bool	last_arg_with_wspaces;
	char	*tmp;

	extracted_argument = NULL;
	last_arg_with_wspaces = true;
	variable = expand_variables(&str, command_line);
	tmp = variable;
	while (tmp && tmp[0])
	{
		if (ft_isspace(tmp[0]) == true)
		{
			if (*definitive_content)
				add_exp_arguments(exp_arguments, definitive_content, \
				command_line);
			while (tmp && tmp[0] && last_arg_with_wspaces == true)
			{
				cut_variable_on_whitespaces(exp_arguments, &tmp, \
				&last_arg_with_wspaces, command_line);
			}
		}
		else
		{
			extract_argument_until_next_whitespace_or_dollar(&tmp, \
			&extracted_argument, command_line);
			add_to_definitive_content(definitive_content, \
			extracted_argument, command_line, variable);
		}
	}
	variable = free_and_null(variable);
}
