#include "minishell.h"

static void	expand_string_between_single_quotes(char **str)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (*str && str[0][i])
	{
		if (str[0][i] == '$')
		{
			i += get_len_and_extract_after_first_dollar(&str[0][i], &tmp);
			expand_string_after_dollar(&tmp);
		}
		else
			i += get_len_and_extract_until_next_dollar(&str[0][i], &tmp);
		if (!result)
			result = ft_strdup_freed(tmp);//malloc à protéger
		else
			result = ft_strjoin_freed(result, tmp);//malloc à protéger
	}
	free(*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}

static int	expand_content_when_dollar_first(char *str, char **tmp)
{
	int	len;

	len = 0;
	if (str[1] == '\"' || str[1] == '\'')
	{
		*tmp = ft_strdup("$");//malloc à protéger
		len += 1;
	}
	else
	{
		len += get_len_and_extract_after_first_dollar(str, tmp);
		expand_string_after_dollar(tmp);
	}
	return (len);
}

static int	expand_content_when_dollar_not_first(char *str, char **tmp)
{
	int	len;

	len = 0;
	if (str[0] == '\"')
		len += get_len_and_extract_between_double_quotes(str, tmp);
	else if (str[0] == '\'')
	{
		len += get_len_and_extract_with_single_quotes(str, tmp);
		if (strcspn(*tmp, "$") < ft_strlen(*tmp))
			expand_string_between_single_quotes(tmp);
	}
	else if (ft_isspace(str[0]) == 0)
		len += get_len_and_extract_until_next_quote_or_dollar(str, tmp);
	else
		len += get_len_and_extract_until_next_separator(str, tmp);
	return (len);
}

void	complete_expand_content(char **str, t_command_line *command_line)
{
	int		i;
	char	*tmp;
	char	*result;

	i = 0;
	result = NULL;
	while (str[0][i])
	{
		if (str[0][i] == '$')
		{
			if (str[0][i + 1] == '?')
			{
				tmp = ft_itoa(command_line->previous_exit_code);//malloc à protéger
				i += 2;
			}
			else
				i += expand_content_when_dollar_first(&str[0][i], &tmp);
		}
		else
			i += expand_content_when_dollar_not_first(&str[0][i], &tmp);
		if (!result)
			result = ft_strdup_freed(tmp);//malloc à protéger
		else
			result = ft_strjoin_freed(result, tmp);//malloc à protéger
	}
	free(*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}

