/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:59 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/30 12:41:21 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_exec_struct **exec_struct)
{
	int					*fd_out;
	t_exec_substring	*cursor;

	cursor = (*exec_struct)->exec_substrings;
	fd_out = &cursor->fd_out;
	if (cursor->exec_arguments)
	{
		if (cursor->exec_redirections)
			*fd_out = search_last_output(cursor->exec_redirections, *fd_out);
		if (cursor->exec_arguments->is_builtin == IOPUT_NOT_ACCEPTED && \
		ft_lst_size7(cursor) == 1)
		{
			if (*fd_out > 0)
				exec_builtin(*exec_struct, cursor, NULL);
			return ;
		}
	}
	substrings_execution(exec_struct);
}
