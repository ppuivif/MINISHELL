/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_line_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:14 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 10:06:04 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_command_line(t_command_line **command_line)
{
	if (*command_line)
	{
		if ((*command_line)->substrings)
			free_substring(&(*command_line)->substrings);
		command_line = free_and_null(*command_line);
	}
}
