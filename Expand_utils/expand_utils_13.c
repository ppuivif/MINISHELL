/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_13.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/02 11:58:39 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assignment_ambiguous_redirection( \
t_expanded_redirection *exp_redirection, t_exec_redirection **exec_redirection)
{
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	(*exec_redirection)->fd_output = -1;
	(*exec_redirection)->fd_input = -1;
	ft_putstr_fd(exp_redirection->content, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (1);
}

int	check_outfile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	if (exp_redirection->t_redirection == REDIRECTION_OUTFILE)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (exp_redirection->t_redirection == REDIRECTION_APPEND)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	if ((*exec_redirection)->fd_output == -1)
	{
		perror(exp_redirection->content);
		return (1);
	}
	return (0);
}

int	check_infile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	int	return_value;

	return_value = 0;
	(*exec_redirection)->fd_input = open(exp_redirection->content, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		if (access(exp_redirection->content, F_OK) == -1)
			perror(exp_redirection->content);
		else
			perror(exp_redirection->content);
		return_value = 1;
	}
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	return (return_value);
}
