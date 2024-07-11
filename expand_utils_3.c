/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:51 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/11 06:33:52 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_variable_content_in_envp(char *variable, t_envp_struct *envp_struct)
{
	int				n;
	t_envp_struct	*cursor;
	char			*result;

	n = ft_strlen (variable);
	cursor = envp_struct;
	result = NULL;
	while (cursor)
	{
		if (ft_strncmp(variable, cursor->name, n) == 0)
		{
			result = ft_strdup(cursor->value);
			return (result);
		}
		cursor = cursor->next;
	}
	return (result);
}

static int	expand_variables_when_dollar_first(char *remaining_line, char **result, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*tmp;

	len_to_cut = 0;
	if ((remaining_line[1] && ft_isspace(remaining_line[1]) == false))
	{
		if (remaining_line[1] == '\"' || remaining_line[1] == '\'')
			*result = ft_strdup("");
		else
		{
			len_to_cut = (int)strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
			tmp = ft_substr(&remaining_line[1], 0, len_to_cut);//malloc à protéger
			*result = get_variable_content_in_envp(tmp, envp_struct); 
			tmp = free_and_null(tmp);
			if (!*result)
				*result = ft_strdup("");
		}
	}
	else
		*result = ft_strdup("$");
	return (len_to_cut);
}

static char	*expand_variables(char **remaining_line, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		len_to_cut = expand_variables_when_dollar_first(remaining_line[0], &result, envp_struct);
		*remaining_line += len_to_cut + 1;
	}
	else
	{
		len_to_cut = (int)strcspn(remaining_line[0], "$\0");
		result = ft_substr(remaining_line[0], 0, len_to_cut);//malloc à protéger
		*remaining_line += len_to_cut;
	}
	return (result);
}


static int	get_content(t_expanded_argument **exp_arguments, char *extracted_argument)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
	{
		exp_argument->alloc_succeed = false;//return error alloc ?
		return (-1);
	}
	exp_argument->content = ft_strdup(extracted_argument);
	extracted_argument = free_and_null(extracted_argument);
	ft_lst_add_back5(exp_arguments, exp_argument);
	return (0);
}

static void	extract_argument_until_next_whitespace_or_dollar(char **str, \
char **extracted_argument)
{
	size_t	len_to_next_separator;

	if (**str == '$')
		len_to_next_separator = 1;
	else
		len_to_next_separator = strcspn(*str, "$ \t\n\v\f\r\0");
//	printf("len : %ld\n", len_to_next_separator);
//	printf("str : %s\n", *str);
	*extracted_argument = ft_substr(*str, 0, len_to_next_separator);//malloc à protéger
//	printf("str : %s\n", (*extracted_argument));
	(*str) += len_to_next_separator;
//	printf("str : %s\n", *str);
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
	if (is_last_argument(str) == true && strcspn(str, " \t\n\v\f\r") < len_to_end)
		return (true);
	return (false);
}



void	cut_variable_on_whitespaces(t_expanded_argument **exp_arguments, char **variable, bool *last_arg_with_wspaces)
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
				extract_argument_until_next_whitespace_or_dollar(variable, &extracted_argument);
				get_content(exp_arguments, extracted_argument);
				*last_arg_with_wspaces = true;
			}
			else
				*last_arg_with_wspaces = false;
		}				
		else
		{
			extract_argument_until_next_whitespace_or_dollar(variable, &extracted_argument);
			get_content(exp_arguments, extracted_argument);
			*last_arg_with_wspaces = true;
		}
	}
}


void	expand_string_after_dollar1(char **str, t_envp_struct *envp_struct)
{
	char	*remaining_line;
	char	*variable;
	char	*result;

	result = NULL;
	remaining_line = *str;
	while (remaining_line && remaining_line[0])
	{
		variable = expand_variables(&remaining_line, envp_struct);
		if (!result)
			result = ft_strdup(variable);//malloc à protéger
		else
			result = ft_strjoin_freed(result, variable);//malloc à protéger
	}
	*str = free_and_null (*str);
	*str = ft_strdup_freed(result);//malloc à protéger
	variable = free_and_null(variable);
}


void	expand_string_after_dollar2(char *str, t_expanded_argument **exp_arguments,\
t_envp_struct *envp_struct, char **definitive_content)
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
				cut_variable_on_whitespaces(exp_arguments, &tmp, &last_arg_with_wspaces);
//				printf ("tmp : %s\n", tmp);
			}
		}
		else
		{
			extract_argument_until_next_whitespace_or_dollar(&tmp, &extracted_argument);
			if (add_to_definitive_content(definitive_content, extracted_argument) == -1)
//				add_exp_arguments(exp_arguments, definitive_content);
//			else
				printf("error\n");
		}				
	}
	variable = free_and_null(variable);
}
