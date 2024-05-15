/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:10:24 by ppuivif           #+#    #+#             */
/*   Updated: 2024/05/15 10:51:13 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/linked_list_utils.h"

int	init_argument_struct(t_native_argument **n_argument)
{
	*n_argument = ft_calloc(1, sizeof(t_native_argument));
	if (!*n_argument)
		return (-1);
	(*n_argument)->content = NULL;
	(*n_argument)->next = NULL;
	return (0);
}

int	init_redirection_struct(t_native_redirection **n_redirection)
{
	*n_redirection = ft_calloc(1, sizeof(t_native_redirection));
	if (!*n_redirection)
		return (-1);
	(*n_redirection)->content = NULL;
	(*n_redirection)->e_redirection = 4;
	(*n_redirection)->next = NULL;
	return (0);
}

int	init_substring_struct(t_substring **substring)
{
	*substring = ft_calloc(1, sizeof(t_substring));
	if (!*substring)
		return (-1);	
	(*substring)->remaining_line = NULL;
	(*substring)->n_arguments = NULL;
	(*substring)->n_redirections = NULL;
	(*substring)->next = NULL;
	return (0);
}

int	init_command_line_struct(t_command_line **command_line)
{
	*command_line = ft_calloc(1, sizeof(t_command_line));
	if (!*command_line)
		return (-1);
	(*command_line)->exit_code = 0;
	(*command_line)->substrings = NULL;
	return (0);
}