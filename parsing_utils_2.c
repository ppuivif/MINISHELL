/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:36:43 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/15 17:33:09 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	is_content_empty(char *remaining_line)
{
	if (ft_strlen(skip_first_whitespaces(remaining_line)) == 0)
		return (true);
	else
		return (false);
}*/

/*static int	is_a_quote_before_separator(char *remaining_line)
{
	int	len;
	int	len_to_separator;
	int	len_to_quote;
	
	len = ft_strcspn(remaining_line, "\'\"");
	len_to_separator = ft_strcspn(remaining_line, "<>| \t\n\0");
	if (len < len_to_separator)
		return (true);
	else
		return (false);
}*/

/*static int	count_len_to_next_quotes(char *remaining_line, char *c, int flag)
{
	int	j;
	int	len_to_quote;
	int	len_to_end;
	int	status_code;

	j = 1;
	flag += 1;
	len_to_quote = ft_strcspn(&remaining_line[1], c);
	len_to_end = (int)ft_strlen(&remaining_line[1]);
	status_code = 0;
	if (len_to_quote == len_to_end)
		return (-1);//syntax_error : no second quote after first one
	while (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
	{
		if ((len_to_quote + flag + j) <= (len_to_end + 1) &&
			(remaining_line[len_to_quote + flag + j] == '\'' || \
		remaining_line[len_to_quote + flag + j] == '\"'))
			status_code = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], \
			(char []){remaining_line[len_to_quote + flag + j], '\0'}, 0);
//		if (((len_to_quote + flag + j) <= (len_to_end + 1)) && \
//		(remaining_line[len_to_quote + flag + j] == '\''))
//			status_code = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\'", 0);
//		else if ((len_to_quote + flag + j) <= (len_to_end + 1) && \
//		remaining_line[len_to_quote + flag + j] == '\"')
//			status_code = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\"", 0);
		if (status_code == -1)
			return (-1);//syntax_error : no second quote after first one
		len_to_quote += status_code;
		if (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
			j++;
	}
	return (len_to_quote + (flag + 1) + (j - 1));
}*/

static bool		is_there_a_second_quote(char *str, char *c)
{
	int	len_to_quote;
	int	len_to_end;

	len_to_quote = ft_strcspn(str, c);
	len_to_end = (int)ft_strlen(str);
	
	if (len_to_quote == len_to_end)
		return (false);
	return (true);
}

static int	count_len_to_next_quotes(char *remaining_line, char *c, int flag)
{
	int	j;
	int	len_to_quote;
	int	status_code;
	int	len_to_end;

	j = 1;
	flag += 1;
	len_to_quote = ft_strcspn(&remaining_line[1], c);
	len_to_end = (int)ft_strlen(&remaining_line[1]);
	status_code = 0;
	if (is_there_a_second_quote(&remaining_line[1], c) == false)
		return (-1);
	while (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
	{
		if (((len_to_quote + flag + j) <= (len_to_end + 1)) && \
		(remaining_line[len_to_quote + flag + j] == '\''))
			status_code = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\'", 0);
		else if ((len_to_quote + flag + j) <= (len_to_end + 1) && \
		remaining_line[len_to_quote + flag + j] == '\"')
			status_code = count_len_to_next_quotes(&remaining_line[len_to_quote + flag + j], "\"", 0);
		if (status_code == -1)
			return (-1);//syntax_error : no second quote after first one
		len_to_quote += status_code;
		if (check_char_validity(remaining_line, len_to_quote, flag, j) == 0)
			j++;
	}
	return (len_to_quote + (flag + 1) + (j - 1));
}

static int	count_len_to_reach_quote_or_separator(char *remaining_line)
{
	int	len;
	int	len_to_separator;
	int	len_to_quote;

/*	if (is_content_empty(remaining_line) == true)
		return (-1);//syntax_error*/
	len = ft_strcspn(remaining_line, "\'\"");
	len_to_separator = ft_strcspn(remaining_line, "<>| \t\n\0");
	len_to_quote = 0;
	if (len < len_to_separator)
	{
		while (remaining_line[0] && remaining_line[0] != '\'' && \
		remaining_line[0] != '\"')
			remaining_line++;
		if (remaining_line[0] == '\'')
			len_to_quote = count_len_to_next_quotes(remaining_line, "\'", 0);
		if (remaining_line[0] == '\"')
			len_to_quote = count_len_to_next_quotes(remaining_line, "\"", 0);
		if (len_to_quote == -1)
			return (-1);//syntax_error : no second quote after first one
		len += len_to_quote;
	}
	else
		len = len_to_separator;
	return (len);
}

int	count_len_to_cut(char *remaining_line)
{
	int	len_to_quote;
	int	len;

	len_to_quote = 0;
	len = 0;
	if (remaining_line[0] == '\'')
		len_to_quote = count_len_to_next_quotes(remaining_line, "\'", 0);
	else if (remaining_line[0] == '\"')
		len_to_quote = count_len_to_next_quotes(remaining_line, "\"", 0);
	else
		len = count_len_to_reach_quote_or_separator(remaining_line);
	if (len_to_quote == -1 || len == -1)
		return (-1);//syntax_error
	len += len_to_quote;
	return (len);
}
