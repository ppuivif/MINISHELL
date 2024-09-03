/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:20 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/03 09:39:32 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_exec_redirection_struct(t_expanded_redirection \
*exp_redirection, t_exec_substring **exec_substring, \
t_exec_struct **exec_struct)
{
	int					status_code;
	t_exec_redirection	*exec_redirection;

	status_code = 0;
	init_exec_redirection_struct(&exec_redirection, exec_struct);
	status_code = open_and_check_file(exp_redirection, &exec_redirection, \
	exec_substring);
	(*exec_struct)->command_line->current_exit_code = status_code;
	if (status_code)
		(*exec_substring)->is_previous_file_opened = false;
	ft_lst_add_back8(&(*exec_substring)->exec_redirections, exec_redirection);
}

static void	build_exec_argument_struct(t_expanded_argument *exp_argument, \
t_exec_substring **exec_substring, t_exec_struct **exec_struct)
{
	t_exec_argument	*exec_argument;

	init_exec_argument_struct(&exec_argument, exec_struct);
	exec_argument->argument = exp_argument->content;
	ft_lst_add_back9(&(*exec_substring)->exec_arguments, exec_argument);
}

static void	build_exec_substring_struct(t_substring *substring, \
t_exec_struct **exec_struct)
{
	t_exec_substring		*exec_substring;
	t_expanded_redirection	*tmp1;
	t_expanded_argument		*tmp2;

	init_exec_substring_struct(&exec_substring, exec_struct);
	tmp1 = substring->exp_redirections;
	tmp2 = substring->exp_arguments;
	(*exec_struct)->command_line->current_exit_code = 0;
	while (tmp1)
	{
		build_exec_redirection_struct(tmp1, &exec_substring, exec_struct);
		tmp1 = tmp1->next;
	}
	while (tmp2)
	{
		build_exec_argument_struct(tmp2, &exec_substring, exec_struct);
		tmp2 = tmp2->next;
	}
	if (exec_substring->exec_arguments)
		check_exec_arguments(&exec_substring, exec_struct);
	ft_lst_add_back7(&(*exec_struct)->exec_substrings, exec_substring);
}

void	build_exec_struct(t_exec_struct **exec_struct)
{
	t_substring	*tmp;

	tmp = (*exec_struct)->command_line->substrings;
	while (tmp)
	{
		search_heredoc_and_modify_exp_redirec(tmp, \
		exec_struct);
		tmp = tmp->next;
	}
	if ((*exec_struct)->command_line->current_exit_code)
		return ;
	tmp = (*exec_struct)->command_line->substrings;
	while (tmp)
	{
		build_exec_substring_struct(tmp, exec_struct);
		tmp = tmp->next;
	}
}
