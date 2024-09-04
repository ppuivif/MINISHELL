/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:51 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/30 14:45:05 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable_content_in_envp(char *variable, \
t_command_line **command_line)
{
	t_envp_struct	*cursor;
	char			*result;

	cursor = (*command_line)->envp_struct;
	result = NULL;
	while (cursor)
	{
		if (ft_strcmp(variable, cursor->name) == 0)
		{
			result = ft_strdup(cursor->value);
			if (!result)
				error_allocation_command_line_and_exit(command_line);
			return (result);
		}
		cursor = cursor->next;
	}
	return (result);
}

static int	simple_expand_variables_when_dollar_first(char \
*remaining_line, char **result, t_command_line **command_line)
{
	int		len_to_cut;
	char	*tmp;

	len_to_cut = strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
	tmp = ft_substr(&remaining_line[1], 0, len_to_cut);
	if (!tmp)
		error_allocation_command_line_and_exit(command_line);
	*result = get_variable_content_in_envp(tmp, command_line);
	tmp = free_and_null(tmp);
	if (!(*result))
		*result = ft_strdup("");
	if (!(*result))
		error_allocation_command_line_and_exit(command_line);
	return (len_to_cut);
}

static int	expand_variables_when_dollar_first(char \
*remaining_line, char **result, t_command_line **command_line)
{
	int		len_to_cut;

	len_to_cut = 0;
	if ((remaining_line[1] && ft_isspace(remaining_line[1]) == false))
	{
		if (remaining_line[1] == '\"' || remaining_line[1] == '\'')
		{
			*result = ft_strdup("");
			if (!(*result))
				error_allocation_command_line_and_exit(command_line);
		}
		else
			len_to_cut = simple_expand_variables_when_dollar_first \
			(remaining_line, result, command_line);
	}
	else
		*result = ft_strdup("$");
	if (!(*result))
		error_allocation_command_line_and_exit(command_line);
	return (len_to_cut);
}

char	*expand_variables(char **remaining_line, t_command_line **command_line)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		len_to_cut = expand_variables_when_dollar_first(remaining_line[0], \
		&result, command_line);
		*remaining_line += len_to_cut + 1;
	}
	else
	{
		len_to_cut = ft_strcspn(remaining_line[0], "$\0");
		result = ft_substr(remaining_line[0], 0, len_to_cut);
		if (!result)
			error_allocation_command_line_and_exit(command_line);
		*remaining_line += len_to_cut;
	}
	return (result);
}
