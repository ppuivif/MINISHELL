/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:34 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:09:38 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_ambiguous_redirection(char *extracted_line)
{
	if (ft_strlen(extracted_line) == 0)
		return (true);
	if (strcspn(extracted_line, " \t\n\v\f\r\0") < ft_strlen(extracted_line))
		return (true);
	return (false);
}

static size_t	common_extract_and_expand_content_of_redirections(char *content, char **extracted_line, t_command_line **command_line)
{
	size_t	len;

	len = 0;
	if (content[0] == '\'')
		len = get_len_and_extract_between_single_quotes \
		(&content[1], extracted_line);
	else if (content[0] == '\"')
	{
		len = get_len_and_extract_between_double_quotes \
		(&content[1], extracted_line);
		if (strcspn(*extracted_line, "$") < ft_strlen(*extracted_line))
			complete_expand_content_of_redirections(extracted_line, command_line);
	}
	else if (content[0] == '$')
	{
		len = simple_expand_content_of_redirections(content, extracted_line, command_line);
		if (is_ambiguous_redirection(*extracted_line) == true)
			len = -2;
	}
	else
		len = get_len_and_extract_until_next_quote_or_dollar \
		(content, extracted_line);
	return (len);
}

static size_t	heredoc_extract_and_expand_content_of_redirections(char *content, char **extracted_line, bool *flag_for_expand)
{
	size_t	len;

	len = 0;
	if (content[0] == '$' && (content[1] == '\'' || content[1] == '\"'))
	{
		(*extracted_line) = ft_strdup("");
		if (!(*extracted_line))
			return (-1);
		len = 1;
	}
	else if (content[0] == '\'')
	{
		len = get_len_and_extract_between_single_quotes \
		(&content[1], extracted_line);
		*flag_for_expand = false;
	}
	else if (content[0] == '\"')
	{
		len = get_len_and_extract_between_double_quotes \
		(&content[1], extracted_line);
		*flag_for_expand = false;
	}
	else
		len = get_len_and_extract_until_next_quote \
		(content, extracted_line);
	return (len);
}

static int	get_definitive_content_of_redirections(char *content, char **definitive_content, \
int t_redirection, t_command_line **command_line, bool *flag_for_expand)
{
	int		len;
	char	*extracted_line;

	len = 0;
	if (t_redirection != 4)
	{
		len = (int)common_extract_and_expand_content_of_redirections \
		(content, &extracted_line, command_line);
		if (len == -2)
		{
			extracted_line = free_and_null(extracted_line);
			return (-2);//ambiguous_redirection
		}
	}
	else
		len = (int)heredoc_extract_and_expand_content_of_redirections \
		(content, &extracted_line, flag_for_expand);
	if (!extracted_line || len == -1)
		return (-1);
	if (!(*definitive_content))
		*definitive_content = ft_strdup(extracted_line);
	else
		*definitive_content = ft_strjoin_freed(*definitive_content, \
		extracted_line);
	extracted_line = free_and_null(extracted_line);
	if (!definitive_content)
		return (-1);
	return (len);
}

void	expand_redirections(t_substring *substring, \
t_native_redirection *n_redirection, t_command_line **command_line)
{
	int						i;
	int						len;
	t_expanded_redirection	*exp_redirection;
	char					*definitive_content;

	i = 0;
	len = 0;
	exp_redirection = NULL;
	definitive_content = NULL;
	if (init_expanded_redirection_struct(&exp_redirection) == -1)
		error_allocation_command_line_and_exit(command_line);
	while (n_redirection && n_redirection->content[i])
	{
		len = get_definitive_content_of_redirections(&n_redirection->content[i], \
		&definitive_content, n_redirection->t_redirection, command_line, \
		&exp_redirection->flag_for_expand);
		if (len == -2)
		{
			ft_putstr_fd(n_redirection->content, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			exp_redirection = free_and_null(exp_redirection);
			(*command_line)->current_exit_code = 1;
			return ;
		}
		(*command_line)->current_exit_code = 0;
		if (len == -1)
			error_allocation_command_line_and_exit(command_line);
		i += len;
	}
	exp_redirection->t_redirection = n_redirection->t_redirection;
	exp_redirection->content = definitive_content;
	ft_lst_add_back4(&substring->exp_redirections, exp_redirection);
}
