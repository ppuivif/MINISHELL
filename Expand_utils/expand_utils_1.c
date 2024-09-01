/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:41 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/31 16:37:17 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_and_extract_between_quotes(char *str, \
char **extracted_line, t_command_line **command_line, char quote_type)
{
	int	len;
	int	len_to_next_quote;

	len = 0;
	len_to_next_quote = 0;
	while (str && str[len_to_next_quote] != quote_type)
		len_to_next_quote++;
	*extracted_line = ft_substr(str, 0, len_to_next_quote);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	len = len_to_next_quote + 2;
	return (len);
}

int	get_len_and_extract_with_single_quotes(char *str, \
char **extracted_line, t_command_line **command_line)
{
	int	len;
	int	len_to_next_single_quote;

	len = 0;
	len_to_next_single_quote = ft_strcspn(&str[1], "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote + 2);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	if (len_to_next_single_quote == (int)ft_strlen(&str[1]))
		len = len_to_next_single_quote + 1;
	else
		len = len_to_next_single_quote + 2;
	return (len);
}

int	get_len_and_extract_until_next_quote(char *str, char **extracted_line, \
t_command_line **command_line)
{
	int	len;
	int	len_to_next_quote;

	len_to_next_quote = ft_strcspn(str, "\"\'");
	*extracted_line = ft_substr(str, 0, len_to_next_quote);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	len = len_to_next_quote;
	return (len);
}

int	get_len_and_extract_until_next_dollar(char *str, char **extracted_line, \
t_command_line **command_line)
{
	int	len;
	int	len_to_next_dollar;

	len_to_next_dollar = ft_strcspn(str, "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar);
	if (!(*extracted_line))
		error_allocation_command_line_and_exit(command_line);
	len = len_to_next_dollar;
	return (len);
}

int	get_len_and_extract_until_next_dollar_first_excluded(char *str, \
char **extracted_line)
{
	int	len;
	int	len_to_next_dollar;

	len_to_next_dollar = ft_strcspn(&str[1], "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar + 1);
	if (!(*extracted_line))
		return (-1);
	len = len_to_next_dollar + 1;
	return (len);
}
