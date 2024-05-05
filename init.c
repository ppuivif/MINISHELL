#include "minishell.h"

void	init_argument_struct(t_native_argument *n_argument)
{
	n_argument->content = NULL;
	n_argument->next = NULL;
}

void	init_redirection_struct(t_native_redirection *n_redirection)
{
	n_redirection->content = NULL;
	n_redirection->e_redirection = 4;
	n_redirection->next = NULL;
}

void	init_substring_struct(t_substring *substring)
{
	substring->flag = NULL;
	substring->remaining_line = NULL;
	substring->n_arguments = NULL;
	substring->n_redirections = NULL;
	substring->next = NULL;
}

void	init_command_line_struct(t_command_line *command_line)
{
	command_line->flag = true;
	command_line->substrings = NULL;
}