/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:46 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/26 14:23:26 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_sign = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

int	open_and_check_file(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_exec_substring **exec_substring, \
t_exec_struct *exec_struct)
{
	int	status_code;

	status_code = 0;
	if ((exp_redirection->t_redirection == REDIRECTION_OUTFILE || \
	exp_redirection->t_redirection == REDIRECTION_APPEND) && \
	(*exec_substring)->is_previous_file_opened == true)
		status_code = check_outfile(exp_redirection, exec_redirection);
	else if (exp_redirection->t_redirection == REDIRECTION_INFILE && \
	(*exec_substring)->is_previous_file_opened == true)
		status_code = check_infile(exp_redirection, exec_redirection);
	else if (exp_redirection->t_redirection == REDIRECTION_HEREDOC)
		status_code = check_heredoc(exp_redirection, exec_redirection, \
		&exec_struct->command_line);
	else if (exp_redirection->t_redirection == REDIRECTION_AMBIGUOUS && \
	(*exec_substring)->is_previous_file_opened == true)
		status_code = assignment_ambiguous_redirection(exp_redirection, \
		exec_redirection);
	else
		status_code = 1;
	return (status_code);
}
