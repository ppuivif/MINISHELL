/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/03 19:38:00 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_heredoc_and_modify_exp_redirec(t_substring *substring, \
t_exec_struct **exec_struct)
{
	t_expanded_redirection	*tmp;

	tmp = substring->exp_redirections;
	while (tmp)
	{
		if (tmp->t_redirection == REDIRECTION_HEREDOC)
			(*exec_struct)->command_line->current_exit_code = \
			open_heredoc_and_modify_exp_redirec(substring, &tmp, exec_struct);
		tmp = tmp->next;
	}
}
