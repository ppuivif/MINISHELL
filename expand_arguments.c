/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 17:45:29 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_to_definitive_content(char **definitive_content, char *extracted_line, \
t_command_line **command_line, char *str)
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
			len = get_len_and_extract_between_quotes \
				(&n_argument_content[1], &extracted_line, command_line, '\'');
			n_argument_content += len;
			add_to_definitive_content(&definitive_content, \
			extracted_line, command_line, NULL);
//			{
//				printf("error_single_quote\n");
//				return (1);
//			}
			if (definitive_content && !n_argument_content[0]) //verify
//			if (definitive_content)
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content, command_line);
		}
		else if (n_argument_content[0] == '\"')
		{
			flag_keep_dollar = true;
			len = get_len_and_extract_between_quotes \
			(&n_argument_content[1], &extracted_line, command_line, '\"');
			n_argument_content += len;
			if (strcspn(extracted_line, "$") < ft_strlen(extracted_line))
				complete_expand_content_of_arguments(&extracted_line, \
				command_line, flag_keep_dollar);
			add_to_definitive_content(&definitive_content, \
			extracted_line, command_line, NULL);
//			{
//				printf("error_double_quote\n");
//				return (1);
//			}
//				no special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content, command_line);
//			else
//				definitive_content = free_and_null(definitive_content);
		}
		else if (n_argument_content[0] == '$')
		{
			len = simple_expand_content_of_arguments(&n_argument_content[0], \
			&substring->exp_arguments, &definitive_content, command_line);
			n_argument_content += len;
/*			if (add_to_definitive_content(&definitive_content, \
			extracted_line) == -2)
			{
				printf("error_$\n");
				return (1);
			}*/
//			special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content, command_line);
//			else
//			definitive_content = free_and_null(definitive_content);
		}
		else
		{
			len = get_len_and_extract_until_next_quote_or_dollar \
			(&n_argument_content[0], &extracted_line, command_line);
			n_argument_content += len;
			add_to_definitive_content(&definitive_content, \
			extracted_line, command_line, NULL);
/*			if (add_to_definitive_content(&definitive_content, \
			extracted_line, command_line) == -1)*/
//			{
//				printf("error_other\n");
//				return (1);
//			}
//			printf("%s\n", definitive_content);
			if (definitive_content && !n_argument_content[0]) //to verify
//			if (definitive_content)
			{
//				printf("n_argument_content : %s\n", n_argument_content);
				add_exp_arguments(&substring->exp_arguments, \
				&definitive_content, command_line);
			}
//			special_treatment with $
		}
	}
	return (0);
}

