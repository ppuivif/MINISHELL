/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_free_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:41 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/19 14:39:20 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_line(char *envp, t_envp_struct **envp_struct)
{
	t_envp_struct	*new_element;

	new_element = NULL;
	if (init_envp_struct(&new_element) == -1)
	{
		ft_putstr_fd("error : an allocation failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_element->name = ft_substr(envp, 0, ft_strcspn(envp, "="));
	new_element->equal = 1;
	new_element->value = ft_substr(envp, ft_strcspn(envp, "=") + 1, \
		ft_strlen(envp));
	ft_lst_add_back6(envp_struct, new_element);
}

void	get_envp(char **envp, t_envp_struct **envp_struct, char *line)
{
	int	i;

	i = 0;
	if (!envp_struct || !envp[0])
	{
		ft_putstr_fd("error\nenvp doesn't exists or is empty\n", 2);
		line = free_and_null(line);
		exit(EXIT_FAILURE);
	}
	while (envp[i])
	{
		add_line(envp[i], envp_struct);
		i++;
	}
}

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
