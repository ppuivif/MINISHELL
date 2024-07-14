/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/14 06:52:51 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int cut_content_on_whitespaces(t_expanded_argument **exp_arguments, char **content, char **extracted_line)
{
//	int		i;
//	int		start;
//	int		flag;
	size_t	len;

//	i = 0;
//	start = 0;
	len = 0;
//	flag = 0;
//	extracted_line = NULL;
//	flag = ft_isspace(*content[i]);
	while (*content && len == 0)
	{
		if (ft_isspace(*content[0]) == true)
		{
			if (extracted_line) //never because free_and_null(extracted_line)
				get_content(exp_arguments, extracted_line);
			*content = skip_first_whitespaces(*content);
			if (ft_strlen(*content) == 0)
				break;
			len = get_len_and_extract_until_next_whitespace_or_dollar(*content, extracted_line);
			get_content(exp_arguments, extracted_line);
		}
		else
		{
			len = get_len_and_extract_until_next_whitespace_or_dollar(*content, extracted_line);
	//		printf("content : %s\n", *content);
		}
//		content += len;
//		printf("len : %ld\n", len);
		(*content) += len;
//		printf("content : %s\n", *content);
	}
	return (len);
}*/

void	add_exp_arguments(t_expanded_argument **exp_arguments, char **definitive_content)
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
			if (add_to_definitive_content(&definitive_content, extracted_line) == -1)
			{
				printf("error_single_quote\n");
				return (1);
			}
			if (definitive_content && !n_argument_content[0])//to verify
//			if (definitive_content)
				add_exp_arguments(&substring->exp_arguments, &definitive_content);
		}
		else if (n_argument_content[0] == '\"')
		{
			flag_keep_dollar = true;
			len = get_len_and_extract_between_double_quotes \
			(&n_argument_content[1], &extracted_line);
			n_argument_content += len;
			if (strcspn(extracted_line, "$") < ft_strlen(extracted_line))
				complete_expand_content_of_arguments(&extracted_line, *command_line, flag_keep_dollar);
			if (add_to_definitive_content(&definitive_content, extracted_line) == -1)
			{
				printf("error_double_quote\n");
				return (1);
			}
//				no special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, &definitive_content);
//			else
//				definitive_content = free_and_null(definitive_content);
		}
		else if (n_argument_content[0] == '$')
		{
			len = simple_expand_content_of_arguments(&n_argument_content[0], &substring->exp_arguments, &definitive_content, command_line);
			n_argument_content += len;
/*			if (add_to_definitive_content(&definitive_content, extracted_line) == -1)
			{
				printf("error_$\n");
				return (1);
			}*/
//			special_treatment with $
			if (definitive_content && !n_argument_content[0])
				add_exp_arguments(&substring->exp_arguments, &definitive_content);
//			else
//			definitive_content = free_and_null(definitive_content);
		}
		else
		{
			len = get_len_and_extract_until_next_quote_or_dollar \
			(&n_argument_content[0], &extracted_line);
			n_argument_content += len;
			if (add_to_definitive_content(&definitive_content, extracted_line) == -1)
			{
				printf("error_other\n");
				return (1);
			}
//			printf("%s\n", definitive_content);
			if (definitive_content && !n_argument_content[0])//to verify
//			if (definitive_content)
			{
//				printf("n_argument_content : %s\n", n_argument_content);
				add_exp_arguments(&substring->exp_arguments, &definitive_content);
			}

//			special_treatment with $
		}
	}
	return (0);
}

/*static size_t	extract_and_expand_content_of_arguments(char *content, \
char **definitive_content, t_expanded_argument **exp_arguments, \
t_command_line **command_line)
{
	size_t	len;
	char *extracted_line;

	if (content[0] == '\'')
	{
		len = (int)get_len_and_extract_between_single_quotes \
		(&content[1], &extracted_line);
		if (add_to_definitive_content(definitive_content, extracted_line) == -1)
			printf("error\n");
	}
	else if (content[0] == '\"')
	{
		len = get_len_and_extract_between_double_quotes \
		(&content[1], &extracted_line);
		if (strcspn(extracted_line, "$") < ft_strlen(extracted_line))
			complete_expand_content(&extracted_line, *command_line);
		if (add_to_definitive_content(definitive_content, extracted_line) == -1)
			printf("error\n");
//			no special_treatment with $
	}
	else if (content[0] == '$')
	{
		len = simple_expand_content(&content[0], &extracted_line, exp_arguments, command_line, 1);
		if (add_to_definitive_content(definitive_content, extracted_line) == -1)
			printf("error\n");
//		special_treatment with $
	}
	else
	{
		len = get_len_and_extract_until_next_quote_or_dollar \
		(&content[0], &extracted_line);
		if (add_to_definitive_content(definitive_content, extracted_line) == -1)
			printf("error\n");
//		special_treatment with $
	}
	return (len);
}*/

/*static int	get_definitive_content_of_arguments(char *content, char **definitive_content, \
t_expanded_argument **exp_arguments, t_command_line **command_line)
{
//	char	*extracted_line;
	int		len;

	len = (int)extract_and_expand_content_of_arguments(content, definitive_content, \
	exp_arguments, command_line);

	return (len);
}*/





/*void	expand_arguments(t_substring *substring, t_native_argument *n_argument, \
t_command_line **command_line)
{
	int					i;
	int					len;
	char				*definitive_content;

	len = 0;
	definitive_content = NULL;
	i = 0;

	if (n_argument && n_argument->content[i])
//	{
		len = get_definitive_content_of_arguments(&n_argument->content[i], \
		&definitive_content, &substring->exp_arguments, command_line);
//		if (len == -1)
//			exp_argument->alloc_succeed = false;//which treatment ?
//		i += len;
//	}
}*/
