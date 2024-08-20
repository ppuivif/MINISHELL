/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 18:14:24 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_string_between_single_quotes(char **str, \
t_envp_struct *envp_struct, t_command_line **command_line)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	tmp = NULL;
	result = NULL;
	while (*str && str[0][i])
	{
		if (str[0][i] == '$')
		{
			i += get_len_and_extract_after_first_dollar(&str[0][i], &tmp);
			expand_string_after_dollar1(&tmp, envp_struct, command_line);
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp);
		if (!result)
		{
			result = ft_strdup_freed(tmp);//malloc à protéger
			tmp = NULL;
		}
		else
		{
			result = ft_strjoin_freed(result, tmp);//malloc à protéger
			tmp = free_and_null(tmp);
		}
	}
	free(*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}

static int	expand_content_of_redirections_when_dollar_first(char *str, \
char **tmp, t_envp_struct *envp_struct, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[1] == '\"' || str[1] == '\'')
	{
		*tmp = ft_strdup("$");//malloc à protéger
		len += 1;
	}
	else
	{
		len += get_len_and_extract_after_first_dollar(str, tmp);
		expand_string_after_dollar1(tmp, envp_struct, command_line);
	}
	return (len);
}

int	expand_content_when_dollar_not_first(char *str, \
char **tmp, t_envp_struct *envp_struct, t_command_line **command_line)
{
	int	len;

	len = 0;
	if (str[0] == '\"')
		len += get_len_and_extract_between_double_quotes(str, tmp);
	else if (str[0] == '\'')
	{
		len += get_len_and_extract_with_single_quotes(str, tmp);
		if (strcspn(*tmp, "$") < ft_strlen(*tmp))
			expand_string_between_single_quotes(tmp, envp_struct, command_line);
	}
	else if (ft_isspace(str[0]) == true)
		len += get_len_and_extract_until_next_quote_or_dollar(str, tmp);
	else
		len += get_len_and_extract_until_next_separator(str, tmp);
	return (len);
}

void	complete_expand_content_of_redirections(char **str, \
t_command_line **command_line)
{
	int		i;
	char	*tmp;
	char	*result;
	int		len;

	i = 0;
	tmp = NULL;
	result = NULL;
	len = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			len = handle_special_characters_after_dollar(&str[0][i], \
			&tmp, command_line, false);
			if (len == -1)
				error_allocation_command_line_and_exit(command_line);
			else if (len == 0)
				i += expand_content_of_redirections_when_dollar_first \
				(&str[0][i], &tmp, (*command_line)->envp_struct, command_line);
			else
				i += (int)len;
		}
		else
			i += expand_content_when_dollar_not_first \
			(&str[0][i], &tmp, (*command_line)->envp_struct, command_line);
		if (!result)
		{
			result = ft_strdup_freed(tmp);//malloc à protéger
			tmp = NULL;
		}
		else
		{
			result = ft_strjoin_freed(result, tmp);//malloc à protéger
			tmp = free_and_null(tmp);
		}
	}
	free(*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}
