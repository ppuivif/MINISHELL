/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:46 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:26:50 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len_and_extract_until_next_dollar_first_dollar_excluded(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_dollar;

	len_to_next_dollar = ft_strcspn(&str[1], "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar + 1);
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_dollar + 1;
	return (len);
}

size_t	get_len_and_extract_until_next_quote_or_dollar(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote_or_dollar;

	len_to_next_quote_or_dollar = ft_strcspn(str, "$\"\'\0");
	*extracted_line = ft_substr(str, 0, len_to_next_quote_or_dollar);//protect
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_quote_or_dollar;
	return (len);
}

size_t	get_len_and_extract_until_next_separator(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = ft_strcspn(str, "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);//protect
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator;
	return (len);
}

size_t	get_len_and_extract_until_next_separator_first_dollar_included\
(char *str, char **extracted_line)
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

size_t	get_len_and_extract_until_next_separator_dollar_excluded(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = ft_strcspn(str, "\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);//malloc à protéger
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_separator;
	return (len);
}

