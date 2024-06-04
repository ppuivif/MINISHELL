#include "minishell.h"

static int	expand_content_heredoc_when_dollar_first(char *str, char **tmp)
{
	int	len;

	len = 0;
	if (str[1] != '\"' && str[1] != '\'' && ft_isspace(str[1]) != 0)
	{
		len += get_len_and_extract_after_first_dollar(str, tmp);
		expand_string_after_dollar(tmp);
	}
	else
		len += get_len_and_extract_until_next_separator_dollar_excluded \
		(str, tmp);
	return (len);
}

size_t	simple_expand_content(char *str, char **extracted_line, \
t_command_line *command_line)
{
	int	len;

	len = 0;
	if (str[1] == '\"' || str[1] == '\'')
	{
		*extracted_line = ft_strdup("");
		len = 1;
	}
	else if (str[1] == '?')
	{
		*extracted_line = ft_strdup(ft_itoa(command_line->exit_code)); 
		len = 2;
	}
	else
	{
		len = get_len_and_extract_after_first_dollar(&str[0], extracted_line);
		expand_string_after_dollar(extracted_line);
	}
	return (len);
}

void	expand_content_when_heredoc(char **str)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
			i += expand_content_heredoc_when_dollar_first(&str[0][i], &tmp);
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
