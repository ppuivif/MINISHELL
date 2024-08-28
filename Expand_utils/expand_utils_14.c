/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_14.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/28 14:57:00 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**search_path(t_exec_struct **exec_struct)
{
	char			**path;
	t_envp_struct	*cursor;

	path = NULL;
	cursor = (*exec_struct)->envp_struct;
	while (cursor)
	{
		if (ft_strcmp(cursor->name, "PATH") == 0)
		{
			path = ft_split(cursor->value, ':');
			if (!path)
				error_allocation_exec_struct_and_exit(exec_struct);
			return (path);
		}
		cursor = cursor->next;
	}
	return (path);
}

void	check_path_in_envp(t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	char	**path_envp;

	path_envp = search_path(exec_struct);
	if (!path_envp || !path_envp[0])
		check_when_no_path(exec_substring, exec_struct, path_envp);
	else
		check_when_path_exists(exec_substring, exec_struct, path_envp);
	path_envp = free_arr(path_envp);
}
