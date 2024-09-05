/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:51 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 10:19:08 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_content(t_expanded_argument **exp_arguments, \
char *extracted_argument, t_command_line **command_line, char **variable)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	init_expanded_argument_struct(&exp_argument, command_line);
	exp_argument->content = ft_strdup(extracted_argument);
	if (!exp_argument->content)
	{
		free(*variable);
		error_allocation_command_line_and_exit(command_line);
	}
	extracted_argument = free_and_null(extracted_argument);
	ft_lst_add_back5(exp_arguments, exp_argument);
	return (0);
}

void	extract_argument_until_next_whitespace_or_dollar(char **str, \
char **extracted_argument, t_command_line **command_line)
{
	size_t	len_to_next_separator;

	if (**str == '$')
		len_to_next_separator = 1;
	else
		len_to_next_separator = ft_strcspn(*str, "$ \t\n\v\f\r\0");
	*extracted_argument = ft_substr(*str, 0, \
	len_to_next_separator);
	if (!(*extracted_argument))
		error_allocation_command_line_and_exit(command_line);
	(*str) += len_to_next_separator;
}

static bool	is_last_argument(char *str)
{
	size_t	len_to_end;
	size_t	i;

	len_to_end = ft_strlen(str);
	i = 0;
	while (str && str[i] && ft_isspace(str[i]) == false)
		i++;
	if (i == len_to_end)
		return (true);
	return (false);
}

static bool	is_last_argument_followed_by_whitespaces(char *str)
{
	size_t	len_to_end;

	len_to_end = ft_strlen(str);
	if (is_last_argument(str) == true && ft_strcspn(str, " \t\n\v\f\r") \
	< (int)len_to_end)
		return (true);
	return (false);
}

void	cut_variable_on_whitespaces(t_expanded_argument **exp_arguments, \
char **variable, bool *last_arg_with_wspaces, t_command_line **command_line)
{
	char	*extracted_argument;

	extracted_argument = NULL;
	*variable = skip_first_whitespaces(*variable);
	if (*variable && *variable[0])
	{
		if (is_last_argument(*variable) == true)
		{
			if (is_last_argument_followed_by_whitespaces(*variable) == true)
			{
				extract_argument_until_next_whitespace_or_dollar \
				(variable, &extracted_argument, command_line);
				get_content(exp_arguments, extracted_argument, command_line, \
				variable);
				*last_arg_with_wspaces = true;
			}
			else
				*last_arg_with_wspaces = false;
			return ;
		}
		extract_argument_until_next_whitespace_or_dollar \
		(variable, &extracted_argument, command_line);
		get_content(exp_arguments, extracted_argument, command_line, variable);
		*last_arg_with_wspaces = true;
	}
}
