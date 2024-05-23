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
	size_t					len;
	char					*extracted_line;
	char					*definitive_content;

	len = 0;
	exp_argument = NULL;
	definitive_content = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
		exp_argument->alloc_succeed = false;
	i = 0;
	while (n_argument && n_argument->content[i])
	{
		if (n_argument->content[i] == '\'')
			len = len_and_extract_between_single_quotes(&n_argument->content[i + 1], &extracted_line);
		else if (n_argument->content[i] == '\"')
			len = len_and_extract_between_double_quotes(&n_argument->content[i + 1], &extracted_line);
/*		{
			len_to_next_quote = strcspn(&n_argument->content[i + 1], "\"");
			extracted_line = ft_substr(&n_argument->content[i + 1], 0, len_to_next_quote);
			if (is_remaining_chars(extracted_line, "$") == 0)
				len = special_expand_content(&extracted_line);
			else
				len = len_to_next_quote + 2;
		}*/
		else
		{
			if (is_remaining_chars(&n_argument->content[i], "$") == 0)
				len = if_dollar_in_string(&n_argument->content[i], &extracted_line);
			else
				len = len_and_extract_until_next_quote(&n_argument->content[i], &extracted_line);
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
		i += len;
	}
	exp_argument->content = definitive_content;
	ft_lst_add_back5(&substring->exp_arguments, exp_argument);
}


size_t	len_and_extract_between_single_quotes(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;
	
	len = 0;
	len_to_next_single_quote = strcspn(str, "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote);
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	len_and_extract_between_double_quotes(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_double_quote;
	
	len = 0;
	len_to_next_double_quote = strcspn(str, "\"");
	*extracted_line = ft_substr(str, 0, len_to_next_double_quote);
	len = len_to_next_double_quote + 2;
	return (len);
}

size_t	len_and_extract_until_next_quote(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote;

	len_to_next_quote = strcspn(str, "\"\'");
	*extracted_line = ft_substr(str, 0, len_to_next_quote);
	len = len_to_next_quote;
	return (len);
}


/*size_t	special_expand_content(char **extracted_line)
{
	int		i;
	size_t	len;
	char 	*tmp;
	char 	*result;

	size_t	len_to_dollar;
	size_t	len_to_double_quote;
		
	result = NULL;
	len_to_dollar = strcspn(*extracted_line, "$");
	len_to_double_quote = strcspn(*extracted_line, "\"");
	while (extracted_line[0][i])
	{
//		if (len_to_dollar == 0)
		if ()
		i++;
		while (ft_isspace(extracted_line[0][i]) == 0)
			i++;
		tmp = substr
		if (!result)
			result = ft_strdup_freed(tmp);
		else
			result = ft_strjoin_freed(result, tmp);
		if (extracted_line[0][i] == "\'")
			 i += strcspn(&extracted_line[0][i], "\'") + 1;
	

	
	}
	free(*extracted_line);
	*extracted_line = ft_strdup_freed[result];
	return (len);
}
*/



size_t	if_dollar_in_string(char *content, char **extracted_line)
{
	int		i;
	size_t	len_to_dollar;
	size_t	len_to_cut;
	size_t	len;
	
	i = 0;
	len_to_cut = 0;
	len = 0;
	len_to_dollar = strcspn(&content[i], "$");
	if (len_to_dollar == 0)
	{
		if (content[i + 1] == '\"' || content[i + 1] == '\'')
		{
			*extracted_line = ft_strdup("");
			len = len_to_dollar + 1;
		}
		else
		{
//			if (strcspn(&content[i + 1], "$") < strcspn(&content[i + 1], "\'\" \t\n\v\f\r\0"))//to complete with whitespaces and $ ?
//				len = 0;
//			else
//				len = 1;
//			len_to_cut = strcspn(&content[i + 1], "$\'\" \t\n\v\f\r\0");//to complete with whitespaces and $ ?
			len_to_cut = strcspn(&content[i + 1], "$\" \t\n\v\f\r\0");//to complete with whitespaces and $ ?
			*extracted_line = ft_substr(&content[i], 0, len_to_cut + 1);
			len = len_to_cut + 1;
			expand_content(extracted_line);
		}
	}
	else
	{
		*extracted_line = ft_substr(&content[i], 0, len_to_dollar);
		len = len_to_dollar;
		expand_content(extracted_line);
	}
	return (len);
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
				result = "";
			else
			{
				len_to_cut = (int)strcspn(&remaining_line[0][1], "$ \t\n\v\f\r\0");
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

int is_remaining_chars(char *str, char *list_of_char)
{
	if(strcspn(str, list_of_char) < ft_strlen(str))
		return (0);
	return (1);
}