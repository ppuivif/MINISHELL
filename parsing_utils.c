/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:36:37 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 16:44:58 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe_first_character(char *remaining_line)
{
	if (remaining_line[0] && remaining_line[0] == '|')
		return (true);
	else
		return (false);
}

int	is_pipe_latest_character(char **remaining_line)
{
	if (*remaining_line[0] && *remaining_line[0] == '|')
	{
		(*remaining_line)++;
		*remaining_line = skip_first_whitespaces(*remaining_line);
		if (ft_strlen(*remaining_line) == 0)
			return (true);
		return (false);
	}
	else
		return (false);
}

unsigned int	count_angled_bracket(char *str)
{
	unsigned int	nmemb;

	nmemb = 0;
	while (str && (*str == '<' || *str == '>' || ft_isspace(*str) == true))
	{
		if (*str == '<' || *str == '>')
			nmemb++;
		str++;
	}
	return (nmemb);
}

static int	count_len_to_next_quote(char **remaining_line, char quote_type)
{
	int len_to_next_quote;
	
	len_to_next_quote = 1;
	while (*remaining_line[0] && *remaining_line[0] != quote_type)
	{
		len_to_next_quote++;
		(*remaining_line)++;
	}
	if (*remaining_line[0] != quote_type)
		return (-1);
	return (len_to_next_quote);
}

int	count_len_to_cut(char *remaining_line)
{
	int		len_to_cut;
	int		len_to_next_quote;
	char	quote_type;
	char	*remaining_line_copy;

	len_to_cut = 0;
	len_to_next_quote = 0;
	remaining_line_copy = remaining_line;
	while (ft_strcspn(remaining_line_copy, "<>| \t\n\0") != 0)
	{
		if (remaining_line_copy[0] == '\'' || remaining_line_copy[0] == '\"')
		{
			quote_type = remaining_line_copy[0];
			remaining_line_copy++;
			len_to_next_quote = count_len_to_next_quote(&remaining_line_copy, \
			quote_type);
			if (len_to_next_quote == -1)
				return (-1);
			else
				len_to_cut += len_to_next_quote;
		}
		remaining_line_copy++;
		len_to_cut++;
	}
	return (len_to_cut);
}
