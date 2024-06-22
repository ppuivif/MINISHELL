#include "minishell.h"

static int	get_content(t_expanded_argument **exp_arguments, char *argument)
{
	t_expanded_argument	*exp_argument;

	exp_argument = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
	{
		exp_argument->alloc_succeed = false;//return error alloc ?
		return (-1);
	}
	exp_argument->content = ft_strdup(argument);
	ft_lst_add_back5(exp_arguments, exp_argument);
	return (0);
}


static size_t	extract_and_expand_content_of_arguments(char *content, \
char **extracted_line, t_command_line **command_line)
{
	size_t	len;

	if (content[0] == '\'')
		len = (int)get_len_and_extract_between_single_quotes \
		(&content[1], extracted_line);
	else if (content[0] == '\"')
	{
		len = get_len_and_extract_between_double_quotes \
		(&content[1], extracted_line);
		if (strcspn(*extracted_line, "$") < ft_strlen(*extracted_line))
			complete_expand_content(extracted_line, *command_line);
//			no special_treatment with $
	}
	else if (content[0] == '$')
		len = simple_expand_content(&content[0], extracted_line, command_line);
//		special_treatment with $
	else
		len = get_len_and_extract_until_next_quote_or_dollar \
		(&content[0], extracted_line);
//		special_treatment with $
	return (len);
}

static int	get_definitive_content_of_arguments(char *content, char **definitive_content, \
t_command_line **command_line)
{
	char	*extracted_line;
	int		len;

	len = (int)extract_and_expand_content_of_arguments(content, &extracted_line, \
	command_line);
	if (!extracted_line)
		return (-1);
	if (!*definitive_content)
		*definitive_content = ft_strdup(extracted_line);
	else
		*definitive_content = \
		ft_strjoin_freed(*definitive_content, extracted_line);
	free(extracted_line);
	extracted_line = NULL;
	if (!*definitive_content)
		return (-1);
	return (len);
}

void	expand_arguments(t_substring *substring, t_native_argument *n_argument, \
t_command_line **command_line)
{
	int					i;
	t_expanded_argument	*exp_argument;
	int					len;
	char				*definitive_content;
	char 	**tmp;

	len = 0;
	exp_argument = NULL;
	definitive_content = NULL;
	tmp = NULL;
	i = 0;
	while ((n_argument->content[i]))
	{
		if (n_argument->content[0] == '$')
		{
			len = get_definitive_content_of_arguments(&n_argument->content[i], \
			&definitive_content, command_line);
			i += len;
//			if (*tmp == 0)
//				get_content(&substring->exp_arguments, "");
//			else
			{
				tmp = ft_split(definitive_content, 32);//add split on $, whitespaces
				while (*tmp)
				{
					get_content(&substring->exp_arguments, *tmp);
					tmp++;
				}
		}
	//prevoir le cas ou la variable contient une variable qui contient une variable ?
		}
		else
		{
			if (init_expanded_argument_struct(&exp_argument) == -1)
			exp_argument->alloc_succeed = false;//return error alloc ?
			while (n_argument && n_argument->content[i])
			{
				len = get_definitive_content_of_arguments(&n_argument->content[i], \
				&definitive_content, command_line);
				if (len == -1)
					exp_argument->alloc_succeed = false;//which treatment ?
				i += len;
			}
			exp_argument->content = definitive_content;
			ft_lst_add_back5(&substring->exp_arguments, exp_argument);
		}
	}
}
