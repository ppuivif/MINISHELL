/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:41 by drabarza          #+#    #+#             */
<<<<<<< HEAD:expand_utils_1.c
/*   Updated: 2024/08/17 19:22:12 by drabarza         ###   ########.fr       */
=======
/*   Updated: 2024/07/16 09:06:35 by ppuivif          ###   ########.fr       */
>>>>>>> PAP:Expand_utils/expand_utils_1.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_len_and_extract_between_single_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;

	len = 0;
	len_to_next_single_quote = ft_strcspn(str, "\'");
<<<<<<< HEAD:expand_utils_1.c
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote);//protection
=======
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote);//malloc à protéger
>>>>>>> PAP:Expand_utils/expand_utils_1.c
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_with_single_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;

	len = 0;
	len_to_next_single_quote = ft_strcspn(&str[1], "\'");
<<<<<<< HEAD:expand_utils_1.c
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote + 2);//protect
=======
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote + 2);//malloc à protéger
>>>>>>> PAP:Expand_utils/expand_utils_1.c
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_between_double_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_double_quote;

	len = 0;
	len_to_next_double_quote = ft_strcspn(str, "\"");
<<<<<<< HEAD:expand_utils_1.c
	*extracted_line = ft_substr(str, 0, len_to_next_double_quote);//protect
=======
	*extracted_line = ft_substr(str, 0, len_to_next_double_quote);//malloc à protéger
>>>>>>> PAP:Expand_utils/expand_utils_1.c
	len = len_to_next_double_quote + 2;
	return (len);
}

size_t	get_len_and_extract_until_next_quote(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote;

	len_to_next_quote = ft_strcspn(str, "\"\'");
	*extracted_line = ft_substr(str, 0, len_to_next_quote);//malloc à protéger
	len = len_to_next_quote;
	return (len);
}

size_t	get_len_and_extract_until_next_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_dollar;

	len_to_next_dollar = ft_strcspn(str, "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar);//malloc à protéger
	len = len_to_next_dollar;
	return (len);
}

size_t	get_len_and_extract_until_next_dollar_first_dollar_excluded(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_dollar;

	len_to_next_dollar = ft_strcspn(&str[1], "$");
<<<<<<< HEAD:expand_utils_1.c
	*extracted_line = ft_substr(str, 0, len_to_next_dollar + 1);//protect
=======
	*extracted_line = ft_substr(str, 0, len_to_next_dollar + 1);//malloc à protéger
>>>>>>> PAP:Expand_utils/expand_utils_1.c
	len = len_to_next_dollar + 1;
	return (len);
}
