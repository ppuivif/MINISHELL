/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_contents.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:33:25 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/03 04:23:17 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_contents(t_command_line **command_line)
{
	t_substring				*cursor1;
	t_native_redirection	*cursor2;
	t_native_argument		*cursor3;
	int						exp_redirection_index;

	cursor1 = (*command_line)->substrings;
	exp_redirection_index = 0;
	while (cursor1)
	{
		cursor2 = cursor1->n_redirections;
		while (cursor2 && (*command_line)->current_exit_code != 2)
		{
			expand_redirections(cursor1, cursor2, command_line, \
			exp_redirection_index);
			cursor2 = cursor2->next;
			exp_redirection_index++;
		}
		cursor3 = cursor1->n_arguments;
		while (cursor3 && (*command_line)->current_exit_code != 2)
		{
			expand_arguments(cursor1, cursor3, command_line);
			cursor3 = cursor3->next;
		}
		cursor1 = cursor1->next;
	}
}
