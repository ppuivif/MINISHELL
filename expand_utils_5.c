#include "minishell.h"

static int is_non_valid_characters(char *str)
{
	if (str[0] && !str[1] && (str[0] == '{' || str[0] == '[' || \
	str[0] == '(' || str[0] == ')'))
		return (true);
	else if (str[0] && str[1] && str[0] == '{' && str[1] != '}')
		return (true);
	else if (str[0] && str[1] && str[0] == '[' && str[1] != ']')
		return (true);
	return (false);
}

static size_t	handle_special_characters_after_dollar(char *str, char **extracted_line, \
t_command_line **command_line)
{
	int	len;
	char	*argv_index;

	len = 0;
	argv_index = NULL;
	if (str[1] == '\"' || str[1] == '\'')
	{
		*extracted_line = ft_strdup("");
		len = 1;
	}
	else if (is_non_valid_characters(&str[1]) == true)
	{
		*extracted_line = ft_strdup("");
		(*command_line)->current_exit_code = 2;
		error_handling(*command_line);
		len = ft_strlen(str);
	}
/*	else if (str[1] == '}' || str[1] == ']')
		len = get_len_and_extract_until_next_separator_first_dollar_included \
		(str, extracted_line);*/
	else if (str[1] == '$')
	{
		*extracted_line = ft_itoa(getpid());
		len = 2;
	}
	else if (str[1] == '?')
	{
		*extracted_line = ft_itoa((*command_line)->previous_exit_code);
		len = 2;
	}
//	else if (str[1] >= '0' && str[1] <= '9')
	else if (str[1] == '0')
	{
		argv_index = ft_substr(str, 1, 1);
//		*extracted_line = ft_strdup((*command_line)->argv[atoi(argv_index)]);
		*extracted_line = ft_strdup(&(*command_line)->argv[atoi(argv_index)][2]);
		argv_index = free_and_null(argv_index);
		len = 2;
	}
	return (len);
}

size_t	simple_expand_content_of_redirections(char *str, char **extracted_line, t_command_line **command_line)
{
	int		len;

	len = handle_special_characters_after_dollar(str, extracted_line, \
	command_line);
	if (len != 0)
		return (len);
	else
	{
		len = get_len_and_extract_after_first_dollar(&str[0], extracted_line);
		expand_string_after_dollar1(extracted_line, (*command_line)->envp_struct);
	}
	return (len);
}


size_t	simple_expand_content_of_arguments(char *str, \
t_expanded_argument **exp_arguments, char **definitive_content, t_command_line **command_line)
{
	int		len;
	char 	*extracted_line;


	extracted_line = NULL;
	len = handle_special_characters_after_dollar(str, &extracted_line, \
	command_line);
	if (len != 0)
	{
		*definitive_content = ft_strdup_freed(extracted_line);
		extracted_line = NULL;
		return (len);
	}
	else
	{
		len = get_len_and_extract_after_first_dollar(&str[0], &extracted_line);
		expand_string_after_dollar2(extracted_line, exp_arguments, (*command_line)->envp_struct, definitive_content);
		extracted_line = free_and_null(extracted_line);
	}
	return (len);
}

static int	expand_content_heredoc_when_dollar_first(char *str, char **tmp, t_envp_struct *envp_struct)
{
	int	len;

	len = 0;
	if (str[1] != '\"' && str[1] != '\'' && (str[1]) != 0)
	{
		len += get_len_and_extract_after_first_dollar(str, tmp);
		expand_string_after_dollar1(tmp, envp_struct);
	}
	else
		len += get_len_and_extract_until_next_separator_dollar_excluded \
		(str, tmp);
	return (len);
}

void	expand_content_when_heredoc(char **str, t_envp_struct *envp_struct)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
			i += expand_content_heredoc_when_dollar_first(&str[0][i], &tmp, envp_struct);
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp);
		if (!result)
		{
			result = ft_strdup_freed(tmp);
			tmp = NULL;
		}
		else
		{
			result = ft_strjoin_freed(result, tmp);
			tmp = free_and_null(tmp);
		}
	}
	free(*str);
	*str = ft_strdup_freed(result);
}

