/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_init_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/20 17:18:42 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"

int	init_native_argument_struct(t_native_argument **n_argument)
{
	*n_argument = ft_calloc(1, sizeof(t_native_argument));
	if (!*n_argument)
		return (-1);
	(*n_argument)->content = NULL;
	(*n_argument)->next = NULL;
	return (0);
}

int	init_native_redirection_struct(t_native_redirection **n_redirection)
{
	*n_redirection = ft_calloc(1, sizeof(t_native_redirection));
	if (!*n_redirection)
		return (-1);
	(*n_redirection)->content = NULL;
	(*n_redirection)->t_redirection = 4;
	(*n_redirection)->next = NULL;
	return (0);
}

int	init_expanded_argument_struct(t_expanded_argument **exp_argument)
{
	*exp_argument = ft_calloc(1, sizeof(t_expanded_argument));
	if (!*exp_argument)
		return (-1);
	(*exp_argument)->alloc_succeed = true;
	(*exp_argument)->content = NULL;
	(*exp_argument)->next = NULL;
	return (0);
}

int	init_expanded_redirection_struct(t_expanded_redirection **exp_redirection)
{
	*exp_redirection = ft_calloc(1, sizeof(t_expanded_redirection));
	if (!*exp_redirection)
		return (-1);
	(*exp_redirection)->content = NULL;
	(*exp_redirection)->t_redirection = 4;
	(*exp_redirection)->flag_for_expand = true;
	(*exp_redirection)->next = NULL;
	return (0);
}
