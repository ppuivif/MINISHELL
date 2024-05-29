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
	t_expanded_redirection	*exp_redirection;
	char					*definitive_content;

	exp_redirection = NULL;
	definitive_content = NULL;
	
	if (init_expanded_redirection_struct(&exp_redirection) == -1)
		exp_redirection->alloc_succeed = false;
	if (redirec(&n_redirection, &definitive_content) == -1)
		exp_redirection->alloc_succeed = false;
	exp_redirection->e_redirection = n_redirection->e_redirection;
	exp_redirection->content = definitive_content;
	ft_lst_add_back4(&substring->exp_redirections, exp_redirection);
}

int	redirec(t_native_redirection **n_redirection, char **definitive_content)
{
	int		 i;
	size_t	len;
	char	*extracted_line;

	i = 0;
	len = 0;
	while (*n_redirection && (*n_redirection)->content[i])
	{
		if ((*n_redirection)->content[i] == '\'')
			len = get_len_and_extract_between_single_quotes \
			(&(*n_redirection)->content[i + 1], &extracted_line);
		else if ((*n_redirection)->content[i] == '\"')
		{
			len = get_len_and_extract_between_double_quotes \
			(&(*n_redirection)->content[i + 1], &extracted_line);
			if (is_remaining_chars(extracted_line, "$") == 0 && \
			(*n_redirection)->e_redirection != 4)
				complete_expand_content(&extracted_line);
		}
		else if ((*n_redirection)->content[i] == '$' && \
		(*n_redirection)->e_redirection != 4)
			len = simple_expand_content(&(*n_redirection)->content[i], &extracted_line);
		else if ((*n_redirection)->e_redirection != 4)
			len = get_len_and_extract_until_next_quote_or_dollar\
			(&(*n_redirection)->content[i], &extracted_line);
		else
			len = get_len_and_extract_until_next_quote \
			(&(*n_redirection)->content[i], &extracted_line);
		if (!extracted_line)
			return (-1);
		if (!(*definitive_content))
			*definitive_content = ft_strdup(extracted_line);
		else
			*definitive_content = ft_strjoin_freed(*definitive_content, extracted_line);
		free(extracted_line);
		extracted_line = NULL;
		if (!definitive_content)
			return (-1);
		i += len;
	}
	return (0);
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
			len = get_len_and_extract_between_single_quotes(&n_argument->content[i + 1], &extracted_line);
		else if (n_argument->content[i] == '\"')
		{
			len = get_len_and_extract_between_double_quotes(&n_argument->content[i + 1], &extracted_line);
			if (is_remaining_chars(extracted_line, "$") == 0)
				complete_expand_content(&extracted_line);
		}
		else if (n_argument->content[i] == '$')
			len = simple_expand_content(&n_argument->content[i], &extracted_line);
		else
			len = get_len_and_extract_until_next_quote_or_dollar(&n_argument->content[i], &extracted_line);
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


size_t	get_len_and_extract_between_single_quotes(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;
	
	len = 0;
	len_to_next_single_quote = strcspn(str, "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote);
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_with_single_quotes(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;
	
	len = 0;
	len_to_next_single_quote = strcspn(&str[1], "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote + 2);
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_between_double_quotes(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_double_quote;
	
	len = 0;
	len_to_next_double_quote = strcspn(str, "\"");
	*extracted_line = ft_substr(str, 0, len_to_next_double_quote);
	len = len_to_next_double_quote + 2;
	return (len);
}

size_t	get_len_and_extract_until_next_quote(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote;

	len_to_next_quote = strcspn(str, "\"\'");
	*extracted_line = ft_substr(str, 0, len_to_next_quote);
	len = len_to_next_quote;
	return (len);
}

size_t	get_len_and_extract_until_next_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_dollar;

	len_to_next_dollar = strcspn(str, "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar);
	len = len_to_next_dollar;
	return (len);
}

size_t	get_len_and_extract_until_next_quote_or_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote_or_dollar;

	len_to_next_quote_or_dollar = strcspn(str, "$\"\'\0");
	*extracted_line = ft_substr(str, 0, len_to_next_quote_or_dollar);
	len = len_to_next_quote_or_dollar;
	return (len);
}

size_t	get_len_and_extract_until_next_separator(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(str, "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);
	len = len_to_next_separator;
	return (len);
}

size_t	get_len_and_extract_after_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(&str[1], "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator + 1);
	len = len_to_next_separator + 1;
	return (len);
}

size_t	simple_expand_content(char *str, char **extracted_line)
{
	int		i;
	int len;
	
	i = 0;
	len = 0;
	if (str[i + 1] == '\"' || str[i + 1] == '\'')
	{
		*extracted_line = ft_strdup("");
		len = 1;
	}
	else
	{
		len = get_len_and_extract_after_dollar(&str[i], extracted_line);
		expand_string_after_dollar(extracted_line);
	}
	return (len);
}

void	complete_expand_content(char **str)
{
	int		i;
	char 	*tmp;
	char 	*result;
	
	i = 0;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			if (str[0][i + 1] == '\"' || str[0][i + 1] == '\'')
			{
				tmp = ft_strdup("$");
				i += 1;
			}
			else
			{
				i += get_len_and_extract_after_dollar(&str[0][i], &tmp);
				expand_string_after_dollar(&tmp);
			}
		}
		else if (str[0][i] == '\"')
			i += get_len_and_extract_between_double_quotes(&str[0][i], &tmp);
		else if (str[0][i] == '\'')
		{
			i += get_len_and_extract_with_single_quotes(&str[0][i], &tmp);
			if (is_remaining_chars(tmp, "$") == 0)
				expand_string_between_single_quotes(&tmp);
		}
		else if (ft_isspace(str[0][i]) == 0)
			i += get_len_and_extract_until_next_quote_or_dollar(&str[0][i], &tmp);
		else
			i += get_len_and_extract_until_next_separator(&str[0][i], &tmp);
		if (!result)
			result = ft_strdup_freed(tmp);
		else
			result = ft_strjoin_freed(result, tmp);
	}
	free(*str);
	*str = ft_strdup_freed(result);
}

void	expand_string_between_single_quotes(char **str)
{
	int		i;
	char	*tmp;
	char 	*result;

	i = 0;
	result = NULL;
	while (*str && str[0][i])
	{
		if (str[0][i] == '$')
		{
			i += get_len_and_extract_after_dollar(&str[0][i], &tmp);
			expand_string_after_dollar(&tmp);
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp);
		if (!result)
			result = ft_strdup_freed(tmp);
		else
			result = ft_strjoin_freed(result, tmp);
	}
	free(*str);
	*str = ft_strdup_freed(result);
}

void	expand_string_after_dollar(char **str)
{
	char	*remaining_line;
	char	*variable;
	char	*result;
	
	result = NULL;
	remaining_line = *str;
	while (remaining_line && remaining_line[0])
	{
		variable = expand_variables(&remaining_line);
		if (!result)
			result = ft_strdup(variable);
		else
			result = ft_strjoin_freed(result, variable);
	}
	free (*str);
	*str = ft_strdup_freed(result);
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