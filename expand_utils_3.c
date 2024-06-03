#include "minishell.h"

static int	expand_variables_when_dollar_first(char *remaining_line, char **result)
{
	int	len_to_cut;

	len_to_cut = 0;
	if ((remaining_line[1] && ft_isspace(remaining_line[1]) != 0))
	{
		if (remaining_line[1] == '\"' || remaining_line[1] == '\'')
			*result = "";
		else
		{
			len_to_cut = (int)strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
			*result = getenv(ft_substr(&remaining_line[1], 0, len_to_cut));
			if (!result)
				*result = "";
		}
	}
	else
		*result = "$";
	return (len_to_cut);
}

static char	*expand_variables(char **remaining_line)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		len_to_cut = expand_variables_when_dollar_first(remaining_line[0], &result);
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
