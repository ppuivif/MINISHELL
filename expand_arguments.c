/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/23 14:29:21 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_content_beginning_single_quotes(char **n_argument_content, \
char **extracted_line, char **definitive_content, t_command_line **command_line)
{
	int	len;

	len = get_len_and_extract_between_quotes \
	(&n_argument_content[0][1], extracted_line, command_line, '\'');
	*n_argument_content += len;
	add_to_definitive_content(definitive_content, \
	*extracted_line, command_line, NULL);
}

static void	expand_content_beginning_double_quotes(char **n_argument_content, \
char **extracted_line, char **definitive_content, t_command_line **command_line)
{
	int		len;
	bool	flag_keep_dollar;

	flag_keep_dollar = false;
	len = get_len_and_extract_between_quotes \
	(&n_argument_content[0][1], extracted_line, command_line, '\"');
	*n_argument_content += len;
	if (strcspn(*extracted_line, "$") < ft_strlen(*extracted_line))
		complete_expand_content_of_arguments(extracted_line, \
		command_line, flag_keep_dollar);
	add_to_definitive_content(definitive_content, \
	*extracted_line, command_line, NULL);
}

static void	expand_content_beginning_dollar(char **n_argument_content, \
t_expanded_argument **exp_arguments, char **definitive_content, \
t_command_line **command_line)
{
	int		len;
	char	*extracted_line;

	extracted_line = NULL;
	len = handle_special_characters_after_dollar(&n_argument_content[0][0], \
	&extracted_line, command_line, false);
	if (len == 0)
	{
		len = get_len_and_extract_after_first_dollar(&n_argument_content[0][0], \
		&extracted_line, command_line);
		expand_string_after_dollar2(extracted_line, exp_arguments, \
		definitive_content, command_line);
		extracted_line = free_and_null(extracted_line);
	}
	else
		add_to_definitive_content(definitive_content, extracted_line, \
		command_line, NULL);
	*n_argument_content += len;
}

static void	expand_simple_content(char **n_argument_content, \
char **extracted_line, char **definitive_content, t_command_line **command_line)
{
	int		len;

	len = get_len_and_extract_until_next_quote_or_dollar \
	(&n_argument_content[0][0], extracted_line, command_line);
	*n_argument_content += len;
	add_to_definitive_content(definitive_content, \
	*extracted_line, command_line, NULL);
}

void	expand_arguments(t_substring *substring, t_native_argument *n_argument, \
t_command_line **command_line)
{
	char	*extracted_line;
	char	*definitive_content;
	char	*n_argument_content;

	definitive_content = NULL;
	extracted_line = NULL;
	n_argument_content = n_argument->content;
	while (n_argument_content && n_argument_content[0])
	{
		if (n_argument_content[0] == '\'')
			expand_content_beginning_single_quotes(&n_argument_content, \
			&extracted_line, &definitive_content, command_line);
		else if (n_argument_content[0] == '\"')
			expand_content_beginning_double_quotes(&n_argument_content, \
			&extracted_line, &definitive_content, command_line);
		else if (n_argument_content[0] == '$')
			expand_content_beginning_dollar(&n_argument_content, \
			&substring->exp_arguments, &definitive_content, command_line);
		else
			expand_simple_content(&n_argument_content, \
			&extracted_line, &definitive_content, command_line);
		if (definitive_content && !n_argument_content[0])
			add_exp_arguments(&substring->exp_arguments, \
			&definitive_content, command_line);
	}
}
