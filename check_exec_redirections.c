#include "minishell.h"

int	open_and_check_file(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	int	return_value;

	return_value = 0;
	if (exp_redirection->e_redirection == 0 || \
	exp_redirection->e_redirection == 3)
	{
		return_value = check_outfile(exp_redirection, exec_redirection);
		return (return_value);
	}
	else if (exp_redirection->e_redirection == 1)
	{
		return_value = check_infile(exp_redirection, exec_redirection);
		return (return_value);
	}
/*	if (exp_redirection->e_redirection == 4)
	{
		return_value = check_heredoc(exp_redirection, exec_redirection);
		return (return_value);
	}*/
	else
		return (-1);
}

int	check_outfile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	if (exp_redirection->e_redirection == 0)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (exp_redirection->e_redirection == 3)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_CREAT, 0644);
	else if ((*exec_redirection)->fd_output == -1)
	{
		perror(exp_redirection->content);
		return (1);
	}
	return (0);
}

int	check_infile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	(*exec_redirection)->fd_input = open(exp_redirection->content, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		if (access(exp_redirection->content, F_OK) == -1)
			perror(exp_redirection->content);
		else
			perror(exp_redirection->content);
		return (1);
	}
	return (0);
}
