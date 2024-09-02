/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:46 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/02 17:48:57 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_and_check_file(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_exec_substring **exec_substring)
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
	else if (exp_redirection->t_redirection == REDIRECTION_AMBIGUOUS && \
	(*exec_substring)->is_previous_file_opened == true)
		status_code = assignment_ambiguous_redirection(exp_redirection, \
		exec_redirection);
	else
		status_code = 1;
	return (status_code);
}
