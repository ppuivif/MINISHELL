#include "minishell.h"

static char	*get_variable_content_in_envp(char *variable, t_envp_struct *envp_struct)
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
			start = strcspn(cursor->content, "=") + 1;//remplacer par ft_strcspn
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
			*result = ft_strdup("");
		else
		{
			len_to_cut = (int)strcspn(&remaining_line[1], "$ \t\n\v\f\r\0");
			tmp = ft_substr(&remaining_line[1], 0, len_to_cut);//malloc à protéger
			*result = get_variable_content_in_envp(tmp, envp_struct); 
			tmp = free_and_null(tmp);
			if (!*result)
				*result = ft_strdup("");
		}
	}
	else
		*result = ft_strdup("$");
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


static int	get_content(t_expanded_argument **exp_arguments, char **extracted_argument)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
	{
		exp_argument->alloc_succeed = false;//return error alloc ?
		return (-1);
	}
	exp_argument->content = ft_strdup(*extracted_argument);
	*extracted_argument = free_and_null(*extracted_argument);
	ft_lst_add_back5(exp_arguments, exp_argument);
	return (0);
}

static void	extract_argument_until_next_whitespace_or_dollar(char **str, \
char **extracted_argument)
{
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(*str, "$ \t\n\v\f\r\0");
	*extracted_argument = ft_substr(*str, 0, len_to_next_separator);//malloc à protéger
	(*str) += len_to_next_separator;
}

void	cut_variable_on_whitespaces(t_expanded_argument **exp_arguments, char **variable)
{
	char	*extracted_argument;

	extracted_argument = NULL;


	*variable = skip_first_whitespaces(*variable);
	extract_argument_until_next_whitespace_or_dollar(variable, &extracted_argument);
	get_content(exp_arguments, &extracted_argument);


}



void	expand_string_after_dollar(char **str, t_expanded_argument **exp_arguments,\
t_envp_struct *envp_struct, char *definitive_content, int flag)
{
	char	*remaining_line;
	char	*variable;
	char	*result;
	char	**extracted_argument;

	result = NULL;
	extracted_argument = NULL;
	remaining_line = *str;
	while (remaining_line && remaining_line[0])
	{
		variable = expand_variables(&remaining_line, envp_struct);
		if (flag == 1)
		{
			printf("variable : %s\n", variable);
			if (ft_isspace(variable[0]) == 0)
				while (variable)
					cut_variable_on_whitespaces(exp_arguments, &variable);
					
					
			else
			{
				extract_argument_until_next_whitespace_or_dollar(&variable, extracted_argument);
				if (add_to_definitive_content(&definitive_content, extracted_argument) == -1)
						printf("error\n");
			}				
		}
		else	
		{
			if (!result)
				result = ft_strdup(variable);//malloc à protéger
			else
				result = ft_strjoin_freed(result, variable);//malloc à protéger
			variable = free_and_null(variable);
		}
	}
	free (*str);
	*str = ft_strdup_freed(result);//malloc à protéger
}
