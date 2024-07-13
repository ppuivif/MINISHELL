/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/13 17:51:10 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_string_between_single_quotes(char **str, t_envp_struct *envp_struct)
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
			expand_string_after_dollar1(&tmp, envp_struct);
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

static int	expand_content_of_redirections_when_dollar_first(char *str, char **tmp, t_envp_struct *envp_struct)
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
		expand_string_after_dollar1(tmp, envp_struct);
	}
	return (len);
}

static int	expand_content_of_arguments_when_dollar_first(char *str, char **tmp, t_envp_struct *envp_struct)
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
		expand_string_after_dollar1(tmp, envp_struct);
	}
	return (len);
}

static int	expand_content_when_dollar_not_first(char *str, char **tmp, t_envp_struct *envp_struct)
{
	int	len;

	len = 0;
	if (str[0] == '\"')
		len += get_len_and_extract_between_double_quotes(str, tmp);
	else if (str[0] == '\'')
	{
		len += get_len_and_extract_with_single_quotes(str, tmp);
		if (strcspn(*tmp, "$") < ft_strlen(*tmp))
			expand_string_between_single_quotes(tmp, envp_struct);
	}
	else if (ft_isspace(str[0]) == true)
		len += get_len_and_extract_until_next_quote_or_dollar(str, tmp);
	else
		len += get_len_and_extract_until_next_separator(str, tmp);
	return (len);
}
void	complete_expand_content_of_redirections(char **str, t_command_line *command_line)
{
	int		i;
	char	*tmp;
	char	*result;
	size_t	len;

	i = 0;
	tmp = NULL;
	result = NULL;
	len = 0;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			len = handle_special_characters_after_dollar(&str[0][i], &tmp, &command_line, false);
			if (len != 0)
				i += (int)len;
			else
				i += expand_content_of_redirections_when_dollar_first(&str[0][i], &tmp, command_line->envp_struct);
		}
		else
			i += expand_content_when_dollar_not_first(&str[0][i], &tmp, command_line->envp_struct);
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

void	complete_expand_content_of_arguments(char **extracted_line, t_command_line *command_line)
{
	int		i;
	char	*tmp;
	char	*result;
	size_t	len;
	bool	flag_keep_dollar;

	i = 0;
	tmp = NULL;
	result = NULL;
	len = 0;
	flag_keep_dollar = false;
	while (extracted_line[0][i])
	{
		if (extracted_line[0][i] == '$')
		{
			len = handle_special_characters_after_dollar(&extracted_line[0][i], &tmp, \
			&command_line, &flag_keep_dollar);
			if (len != 0)
				if (flag_keep_dollar == false)
					i += (int)len;
				else
					i += (int)len - 1;
			else
				i += expand_content_of_arguments_when_dollar_first(&extracted_line[0][i], &tmp, command_line->envp_struct);//to complete whith case of sapces in variable value
		}
		else
			i += expand_content_when_dollar_not_first(&extracted_line[0][i], &tmp, command_line->envp_struct);
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
	free(*extracted_line);
	*extracted_line = ft_strdup_freed(result);//malloc à protéger
}
