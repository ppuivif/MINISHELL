/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 17:42:29 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_string_after_dollar1(char **str, \
t_envp_struct *envp_struct, t_command_line **command_line)
{
	char	*remaining_line;
	char	*variable;
	char	*result;
	int		len;

	result = NULL;
	remaining_line = *str;
	len = 0;
	while (remaining_line && remaining_line[0])
	{
		len = handle_special_characters_after_dollar(remaining_line, \
		&variable, command_line, 1);
		if (len == 0)
			variable = expand_variables(&remaining_line, envp_struct);
		else
			remaining_line += len;
		if (!result)
			result = ft_strdup(variable);//malloc à protéger
		else
			result = ft_strjoin_freed(result, variable);//malloc à protéger
	}
	*str = free_and_null (*str);
	*str = ft_strdup_freed(result);//malloc à protéger
	variable = free_and_null(variable);
}

void	expand_string_after_dollar2(char *str, \
t_expanded_argument **exp_arguments, t_envp_struct *envp_struct, \
char **definitive_content)
{
	char	*variable;
	char	*extracted_argument;
	bool	last_arg_with_wspaces;
	char	*tmp;

//	result = NULL;
	extracted_argument = NULL;
	last_arg_with_wspaces = true;
	variable = expand_variables(&str, envp_struct);
	tmp = variable;
	while (tmp && tmp[0])
	{
//		printf("variable : %s\n", variable);
		if (ft_isspace(tmp[0]) == true)
		{
			if (*definitive_content)
				add_exp_arguments(exp_arguments, definitive_content);
			while (tmp && tmp[0] && last_arg_with_wspaces == true)
			{
				cut_variable_on_whitespaces(exp_arguments, &tmp, \
				&last_arg_with_wspaces);
//				printf ("tmp : %s\n", tmp);
			}
		}
		else
		{
			extract_argument_until_next_whitespace_or_dollar(&tmp, \
			&extracted_argument);
			if (add_to_definitive_content(definitive_content, \
			extracted_argument) == -1)
//				add_exp_arguments(exp_arguments, definitive_content);
//			else
				printf("error\n");
		}
	}
	variable = free_and_null(variable);
}
