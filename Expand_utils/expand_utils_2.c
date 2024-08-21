/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:46 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 17:47:47 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_and_extract_until_next_quote_or_dollar(char *str, \
char **extracted_line, t_command_line **command_line)
{
	int	len;
	int	len_to_next_quote_or_dollar;

	len_to_next_quote_or_dollar = ft_strcspn(str, "$\"\'\0");
	*extracted_line = ft_substr(str, 0, len_to_next_quote_or_dollar);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	len = len_to_next_quote_or_dollar;
	return (len);
}

int	get_len_and_extract_until_next_separator(char *str, \
char **extracted_line)
{
	int	len;
	int	len_to_next_separator;

	len_to_next_separator = ft_strcspn(str, "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);//protect
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator;
	return (len);
}

int	get_len_and_extract_until_next_separator_first_dollar_included\
(char *str, char **extracted_line)
{
	int	len;
	int	len_to_next_separator;

	len_to_next_separator = ft_strcspn(&str[1], "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator + 1);
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator + 1;
	return (len);
}

int	get_len_and_extract_until_next_separator_dollar_excluded(char *str, \
char **extracted_line)
{
	int	len;
	int	len_to_next_separator;

	len_to_next_separator = ft_strcspn(str, "\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator;
	return (len);
}

int	get_len_and_extract_after_first_dollar(char *str, char **extracted_line, \
t_command_line **command_line)
{
	int	len;
	int	len_to_next_separator;

	len_to_next_separator = ft_strcspn(&str[1], "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator + 1);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	len = len_to_next_separator + 1;
	return (len);
}
