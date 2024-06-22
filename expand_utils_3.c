#include "minishell.h"

static char	*get_variable_content(char *variable, t_envp_struct *envp_struct)
{
	int				n;
	int				start;
	int				len;
	t_envp_struct	*cursor;
	char			*result;

	n = ft_strlen (variable);
	cursor = envp_struct;
	result = NULL;
	while (cursor)
	{
		if (ft_strncmp(variable, cursor->content, n) == 0)
		{
			len = ft_strlen(cursor->content);
			start = strcspn(cursor->content, "=") + 1;//remplacer parft_strcspn
			result = ft_substr(cursor->content, start, len);
			return (result);
		}
		cursor = cursor->next;
	}
	return (result);
}

static int	expand_variables_when_dollar_first(char *remaining_line, char **result, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*tmp;

	len_to_cut = 0;
	if ((remaining_line[1] && ft_isspace(remaining_line[1]) != 0))
	{
		if (remaining_line[1] == '\"' || remaining_line[1] == '\'')
			*result = "";
		else
		{
			len_to_cut = (int)strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
			tmp = ft_substr(&remaining_line[1], 0, len_to_cut);//malloc à protéger
			*result = get_variable_content(tmp, envp_struct); 
			free_and_null(tmp);
			if (!*result)
				*result = "";
		}
	}
	else
		*result = "$";
	return (len_to_cut);
}

static char	*expand_variables(char **remaining_line, t_envp_struct *envp_struct)
{
	int		len_to_cut;
	char	*result;

	len_to_cut = 0;
	result = NULL;
	if (remaining_line[0][0] == '$')
	{
		len_to_cut = expand_variables_when_dollar_first(remaining_line[0], &result, envp_struct);
		*remaining_line += len_to_cut + 1;
	}
	else
	{
		len_to_cut = (int)strcspn(remaining_line[0], "$\0");
		result = ft_substr(remaining_line[0], 0, len_to_cut);//malloc à protéger
		*remaining_line += len_to_cut;
	}
	return (result);
}

void	expand_string_after_dollar(char **str, t_envp_struct *envp_struct)
{
	char	*remaining_line;
	char	*variable;
	char	*result;

	result = NULL;
	remaining_line = *str;
	while (remaining_line && remaining_line[0])
	{
		variable = expand_variables(&remaining_line, envp_struct);
		if (!result)
			result = ft_strdup(variable);//malloc à protéger
		else
			result = ft_strjoin_freed(result, variable);//malloc à protéger
	}
	free (*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}
