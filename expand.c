#include "minishell.h"

void	expand_contents(t_command_line **command_line)
{
	t_substring	*tmp1;
	t_native_redirection *tmp2;
	t_native_argument *tmp3;

	tmp1 = (*command_line)->substrings;
	while (tmp1)
	{
		tmp2 = tmp1->n_redirections;
		while (tmp2)
		{
			expand_redirections(tmp1, tmp2);
			if (tmp1->exp_redirections->alloc_succeed == false)
				free_all(command_line);	
			tmp2 = tmp2->next;
		}
		tmp3 = tmp1->n_arguments;
		while (tmp3)
		{
			expand_arguments(tmp1, tmp3);
			if (tmp1->exp_arguments->alloc_succeed == false)
				free_all(command_line);
			tmp3 = tmp3->next;
		}
		tmp1 = tmp1->next;
	}
}


void expand_redirections(t_substring *substring, t_native_redirection *n_redirection)
{
	int	i;
	t_expanded_redirection	*exp_redirection;
	size_t					len_to_next_quote;
	char					*extracted_line;
	char					*definitive_content;


	exp_redirection = NULL;
	definitive_content = NULL;
	if (init_expanded_redirection_struct(&exp_redirection) == -1)
		exp_redirection->alloc_succeed = false;
	i = 0;
	while (n_redirection && n_redirection->content[i])
	{
		if (n_redirection->content[i] == '\'')
		{
			len_to_next_quote = strcspn(&n_redirection->content[i + 1], "\'");
			extracted_line = ft_substr(&n_redirection->content[i + 1], 0, len_to_next_quote);
//			search_variables(extracted_line);
		}
		else if (n_redirection->content[i] == '\"')
		{
			len_to_next_quote = strcspn(&n_redirection->content[i + 1], "\"");
			extracted_line = ft_substr(&n_redirection->content[i + 1], 0, len_to_next_quote);
//			search_variables(extracted_line);
		}
		else
		{
			len_to_next_quote = strcspn(&n_redirection->content[i], "\"\'") - 2;
			extracted_line = ft_substr(&n_redirection->content[i], 0, len_to_next_quote + 2);
		}
		if (!extracted_line)
			exp_redirection->alloc_succeed = false;
		if (!definitive_content)
			definitive_content = ft_strdup(extracted_line);
		else
			definitive_content = ft_strjoin_freed(definitive_content, extracted_line);
		free(extracted_line);
		extracted_line = NULL;
		if (!definitive_content)
			exp_redirection->alloc_succeed = false;
		i += (len_to_next_quote + 2);
	}
	exp_redirection->e_redirection = n_redirection->e_redirection;
	exp_redirection->content = definitive_content;
	ft_lst_add_back4(&substring->exp_redirections, exp_redirection);
}

void expand_arguments(t_substring *substring, t_native_argument *n_argument)
{
	int i;
	t_expanded_argument		*exp_argument;
	size_t					len_to_next_quote;
	size_t					len_to_dollar;
	char					*extracted_line;
	char					*definitive_content;

	exp_argument = NULL;
	definitive_content = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
		exp_argument->alloc_succeed = false;
	i = 0;
	while (n_argument && n_argument->content[i])
	{
		if (n_argument->content[i] == '\'')
		{
			len_to_next_quote = strcspn(&n_argument->content[i + 1], "\'");
			extracted_line = ft_substr(&n_argument->content[i + 1], 0, len_to_next_quote);
		}
		else if (n_argument->content[i] == '\"')
		{
			len_to_next_quote = strcspn(&n_argument->content[i + 1], "\"");
			extracted_line = ft_substr(&n_argument->content[i + 1], 0, len_to_next_quote);
			expand_content(&extracted_line);
		}
		else
		{
			if (strcspn(&n_argument->content[i], "$") < ft_strlen(&n_argument->content[i]))
			{
				len_to_dollar = strcspn(&n_argument->content[i], "$");
				if (len_to_dollar == 0)
				{
					if (n_argument->content[i + 1] == '\"' || n_argument->content[i + 1] == '\'')
						len_to_next_quote = len_to_dollar - 1;
					else
					{
						len_to_next_quote = strcspn(&n_argument->content[i + 1], "\'\"");//to complete with whitespaces and $ ?
						extracted_line = ft_substr(&n_argument->content[i], 0, len_to_next_quote);
						expand_content(&extracted_line);
					}
				}
				else
				{
					extracted_line = ft_substr(&n_argument->content[i], 0, len_to_dollar);
					len_to_next_quote = len_to_dollar - 2;
					expand_content(&extracted_line);
				}
			}
			else
			{
				len_to_next_quote = strcspn(&n_argument->content[i], "\"\'") - 2;
				extracted_line = ft_substr(&n_argument->content[i], 0, len_to_next_quote + 2);
				//expand_content(&extracted_line);
//			}
		}
		if (!extracted_line)
			exp_argument->alloc_succeed = false;
		if (!definitive_content)
			definitive_content = ft_strdup(extracted_line);
		else
			definitive_content = ft_strjoin_freed(definitive_content, extracted_line);
		free(extracted_line);
		extracted_line = NULL;
		if (!definitive_content)
			exp_argument->alloc_succeed = false;
		i += (len_to_next_quote + 2);
	}
	exp_argument->content = definitive_content;
	ft_lst_add_back5(&substring->exp_arguments, exp_argument);
}


void	expand_content(char **extracted_line)
{
	char	*remaining_line;
	char	*variable;
	char	*result;
	
	result = ft_strdup("");
//	remaining_line = skip_first_whitespaces(*extracted_line);
	remaining_line = *extracted_line;
//	if (strcspn(remaining_line, "$") < ft_strlen(remaining_line))
//	{
		while (remaining_line && remaining_line[0])
		{
			variable = expand_variables(&remaining_line);
			if (!result[0])
				result = ft_strdup(variable);
			else
				result = ft_strjoin_freed(result, variable);
		}
		free (*extracted_line);
		*extracted_line = ft_strdup_freed(result);
//	}
}

char *expand_variables(char **remaining_line)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		if ((remaining_line[0][1] && ft_isspace(remaining_line[0][1]) != 0))
		{
			if (remaining_line[0][1] == '\"' || remaining_line[0][1] == '\'')
			{
				len_to_cut = 0;
				result = "";
			}
			else
			{
				len_to_cut = (int)strcspn(&remaining_line[0][1], " \t\n\v\f\r\0");
				result = getenv(ft_substr(&remaining_line[0][1], 0, len_to_cut));
				if (!result)
					result = "";
			}
		}
		else
			result = "$";
		*remaining_line += len_to_cut + 1;
	}
	else
	{
		len_to_cut = (int)strcspn(remaining_line[0], "$\0");
		result = ft_substr(remaining_line[0], 0, len_to_cut);
		*remaining_line += len_to_cut;
	}
	return (result);
}
