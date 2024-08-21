/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_8.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 11:00:32 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_non_valid_characters(char *str)
{
	if (str[0] && !str[1] && (str[0] == '{' || str[0] == '[' || \
	str[0] == '(' || str[0] == ')'))
		return (true);
	else if (str[0] && str[1] && str[0] == '{' && str[1] != '}')
		return (true);
	else if (str[0] && str[1] && str[0] == '[' && str[1] != ']')
		return (true);
	return (false);
}

int	handle_quotes(char **extracted_line, t_command_line **command_line, \
bool flag_keep_dollar)
{
	if (flag_keep_dollar == true)
		*extracted_line = ft_strdup("$");
	else
		*extracted_line = ft_strdup("");
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	return (1);
}

int	handle_non_valid_characters(char *str, char **extracted_line, \
t_command_line **command_line)
{
	int	len;

	len = 0;
	*extracted_line = ft_strdup("");
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	else
	{
		(*command_line)->current_exit_code = 2;
		ft_putstr_fd("syntax error\n", 2);
		len = ft_strlen(str);
	}
	return (len);
}

int	handle_double_dollar(char **extracted_line, t_command_line **command_line)
{
	*extracted_line = ft_itoa(getpid());
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	return (2);
}

int	handle_question_mark(char **extracted_line, t_command_line **command_line)
{
	*extracted_line = ft_itoa((*command_line)->previous_exit_code);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	return (2);
}
