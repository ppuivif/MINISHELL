#include "minishell.h"

void	expand_contents(t_command_line **command_line)
{
	size_t	i;
	size_t	j;
	t_substring	*tmp1;
	t_native_redirection *tmp2;
	t_native_argument *tmp3;
	//t_expanded_redirection	*exp_redirection;
	//t_expanded_argument		*exp_argument;

	i = 0;
	tmp1 = (*command_line)->substrings;
	while ((*command_line)->substrings && i < ft_lst_size1((*command_line)->substrings))
	{
		j = 0;
		tmp2 = tmp1->n_redirections;
		while (tmp1->n_redirections && j < ft_lst_size2(tmp1->n_redirections))
		{
			expand_redirections((*command_line)->substrings, tmp1->n_redirections);
			if ((*command_line)->substrings->exp_redirections->alloc_succeed == false)
				free_all(command_line);	
//			printf("exp_redirection %d : %s\n", exp_redirection->content);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->n_arguments;
		while (tmp1->n_arguments && j < ft_lst_size3(tmp1->n_arguments))
		{
			expand_arguments((*command_line)->substrings, tmp1->n_arguments);
			if ((*command_line)->substrings->exp_arguments->alloc_succeed == false)
				free_all(command_line);
			tmp3 = tmp3->next;
			j++;
		}
		(*command_line)->substrings = (*command_line)->substrings->next;
		i++;
	}
	(*command_line)->substrings = tmp1;
}


void expand_redirections(t_substring *substring, t_native_redirection *n_redirection)
{
	t_expanded_redirection	*exp_redirection;
	size_t					len_to_next_quote;
	char					*extracted_line;

	exp_redirection = NULL;
	if (init_expanded_redirection_struct(&exp_redirection) == -1)
		exp_redirection->alloc_succeed = false;
	if (n_redirection)
	{
		if (n_redirection->content[0] == '\'')
		{
			len_to_next_quote = strspn(&n_redirection->content[1], "\'");
			extracted_line = ft_substr(&n_redirection->content[1], 0, len_to_next_quote);
			n_redirection->content += len_to_next_quote;
//			search_variables(extracted_line);
		}
		if (n_redirection->content[0] == '\"')
		{
			len_to_next_quote = strspn(&n_redirection->content[1], "\"");
			extracted_line = ft_substr(&n_redirection->content[1], 0, len_to_next_quote);
			n_redirection->content += len_to_next_quote;
//			search_variables(extracted_line);
		}
		else
		{
			extracted_line = n_redirection->content;
		}
		if (extracted_line)
		{
			exp_redirection->e_redirection = n_redirection->e_redirection;
			exp_redirection->content = extracted_line;
		}
	}
	ft_lst_add_back4(&substring->exp_redirections, exp_redirection);
}
void expand_arguments(t_substring *substring, t_native_argument *n_argument)
{
	t_expanded_argument		*exp_argument;
	size_t					len_to_next_quote;
	char					*extracted_line;

	exp_argument = NULL;
	if (init_expanded_argument_struct(&exp_argument) == -1)
		exp_argument->alloc_succeed = false;
	if (n_argument)
	{
		if (n_argument->content[0] == '\'')
		{
			len_to_next_quote = strspn(&n_argument->content[1], "\'");
			extracted_line = ft_substr(&n_argument->content[1], 0, len_to_next_quote);
			n_argument->content += len_to_next_quote;
//			search_variables(extracted_line);
		}
		if (n_argument->content[0] == '\"')
		{
			len_to_next_quote = strspn(&n_argument->content[1], "\"");
			extracted_line = ft_substr(&n_argument->content[1], 0, len_to_next_quote);
			n_argument->content += len_to_next_quote;
//			search_variables(extracted_line);
		}
		else
		{
			extracted_line = n_argument->content;
		}
		if (extracted_line)
			exp_argument->content = extracted_line;
	}
	ft_lst_add_back5(&substring->exp_arguments, exp_argument);
}