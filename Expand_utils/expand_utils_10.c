/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_10.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/23 14:38:53 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_definitive_content(char **definitive_content, \
char *extracted_line, t_command_line **command_line, char *str)
{
	if (!*definitive_content)
		*definitive_content = ft_strdup(extracted_line);
	else
		*definitive_content = \
		ft_strjoin_freed(*definitive_content, extracted_line);
	extracted_line = free_and_null(extracted_line);
	if (!*definitive_content)
	{
		free(str);
		error_allocation_command_line_and_exit(command_line);
	}
}

void	check_ambiguous_redirection(char **extracted_line, \
t_native_redirection **n_redirection)
{
	size_t	len;
	size_t	len_to_separator;

	len = ft_strlen(*extracted_line);
	len_to_separator = ft_strcspn(*extracted_line, " \t\n\v\f\r\0");
	if (len == 0 || len_to_separator < len)
		(*n_redirection)->t_redirection = REDIRECTION_AMBIGUOUS;
}

void	add_exp_arguments(t_expanded_argument **exp_arguments, \
char **definitive_content, t_command_line **command_line)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	init_expanded_argument_struct(&exp_argument, command_line);
	exp_argument->content = ft_strdup_freed(*definitive_content);
	*definitive_content = NULL;
	if (!exp_argument->content)
		error_allocation_command_line_and_exit(command_line);
	ft_lst_add_back5(exp_arguments, exp_argument);
}
