/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 16:47:14 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_exp_arguments(t_expanded_argument **exp_arguments, \
char **definitive_content)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
		exp_argument->alloc_succeed = false;//return error alloc ?
	exp_argument->content = ft_strdup_freed(*definitive_content);
	*definitive_content = NULL;
	ft_lst_add_back5(exp_arguments, exp_argument);
}

int	add_to_definitive_content(char **definitive_content, char *extracted_line)
{
	if (!extracted_line)
		return (-1);
	if (!*definitive_content)
		*definitive_content = ft_strdup(extracted_line);
	else
		*definitive_content = \
		ft_strjoin_freed(*definitive_content, extracted_line);
	extracted_line = free_and_null(extracted_line);
//	printf("definitive_content ; %s\n", *definitive_content);
	if (!*definitive_content)
		return (-1);
	return (0);
}

int	expand_arguments(t_substring *substring, t_native_argument *n_argument, \
t_command_line **command_line)
{
	size_t	len;
	char	*extracted_line;
	char	*definitive_content;
	char	*n_argument_content;
	bool	flag_keep_dollar;

	definitive_content = NULL;
	extracted_line = NULL;
	n_argument_content = n_argument->content;
	flag_keep_dollar = false;
	while (n_argument_content && n_argument_content[0])
	{
		if (n_argument_content[0] == '\'')
		{
			len = (int)get_len_and_extract_between_single_quotes \
				(&n_argument_content[1], &extracted_line);
			n_argument_content += len;
			if (add_to_definitive_content(&definitive_content, \
			extracted_line) == -1)
			{
				printf("error_single_quote\n");
				return (1);
			}
			if (definitive_content && !n_argument_content[0]) //verify
//			if (definitive_content)
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content);
		}
		else if (n_argument_content[0] == '\"')
		{
			flag_keep_dollar = true;
			len = get_len_and_extract_between_double_quotes \
			(&n_argument_content[1], &extracted_line);
			n_argument_content += len;
			if (strcspn(extracted_line, "$") < ft_strlen(extracted_line))
				complete_expand_content_of_arguments(&extracted_line, \
				command_line, flag_keep_dollar);
			if (add_to_definitive_content(&definitive_content, \
			extracted_line) == -1)
			{
				printf("error_double_quote\n");
				return (1);
			}
//				no special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content);
//			else
//				definitive_content = free_and_null(definitive_content);
		}
		else if (n_argument_content[0] == '$')
		{
			len = simple_expand_content_of_arguments(&n_argument_content[0], \
			&substring->exp_arguments, &definitive_content, command_line);
			n_argument_content += len;
/*			if (add_to_definitive_content(&definitive_content, \
			extracted_line) == -1)
			{
				printf("error_$\n");
				return (1);
			}*/
//			special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content);
//			else
//			definitive_content = free_and_null(definitive_content);
		}
		else
		{
			len = get_len_and_extract_until_next_quote_or_dollar \
			(&n_argument_content[0], &extracted_line);
			n_argument_content += len;
			if (add_to_definitive_content(&definitive_content, \
			extracted_line) == -1)
			{
				printf("error_other\n");
				return (1);
			}
//			printf("%s\n", definitive_content);
			if (definitive_content && !n_argument_content[0]) //to verify
//			if (definitive_content)
			{
//				printf("n_argument_content : %s\n", n_argument_content);
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content);
			}
//			special_treatment with $
		}
	}
	return (0);
}

