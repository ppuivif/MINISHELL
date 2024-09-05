/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_9.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 09:24:44 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_equals_sign(char **extracted_line, t_command_line **command_line)
{
	*extracted_line = ft_strdup("$=");
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	return (2);
}

int	handle_digits(char *str, char **extracted_line, \
t_command_line **command_line)
{
	char	*argv_index;

	argv_index = ft_substr(str, 1, 1);
	if (!argv_index)
		error_allocation_command_line_and_exit(command_line);
	else if (str[1] == '0' && (*command_line)->argv[ft_atoi(argv_index)])
		*extracted_line = \
		ft_strdup((*command_line)->argv[ft_atoi(argv_index)]);
	else
		*extracted_line = ft_strdup("");
	argv_index = free_and_null(argv_index);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	return (2);
}

int	handle_special_characters_after_dollar(char *str, \
char **extracted_line, t_command_line **command_line, bool flag_keep_dollar)
{
	int		len;

	len = 0;
	if (str[1] == '\"' || str[1] == '\'')
		len = handle_quotes(extracted_line, command_line, flag_keep_dollar);
	else if (is_non_valid_characters(&str[1]) == true)
		len = handle_non_valid_characters(str, extracted_line, command_line);
	else if (str[1] == '$')
		len = handle_double_dollar(extracted_line, command_line);
	else if (str[1] == '?')
		len = handle_question_mark(extracted_line, command_line);
	else if (str[1] == '=')
		len = handle_equals_sign(extracted_line, command_line);
	else if (str[1] >= '0' && str[1] <= '9')
		len = handle_digits(str, extracted_line, command_line);
	return (len);
}

int	simple_expand_content_of_redirections(char *str, \
char **extracted_line, t_command_line **command_line)
{
	int		len;

	len = handle_special_characters_after_dollar(str, extracted_line, \
	command_line, false);
	if (len != 0)
		return (len);
	len = get_len_and_extract_after_first_dollar(&str[0], extracted_line, \
	command_line);
	expand_string_after_dollar1(extracted_line, command_line);
	return (len);
}
