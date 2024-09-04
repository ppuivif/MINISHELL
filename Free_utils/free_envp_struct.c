/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:14 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 09:52:08 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_struct(t_envp_struct **envp_struct)
{
	t_envp_struct	*tmp;

	while (ft_lst_size6(*envp_struct))
	{
		tmp = (*envp_struct)->next;
		(*envp_struct)->name = free_and_null((*envp_struct)->name);
		(*envp_struct)->value = free_and_null((*envp_struct)->value);
		free(*envp_struct);
		*envp_struct = tmp;
	}
}
