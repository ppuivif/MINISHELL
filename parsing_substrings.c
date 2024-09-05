/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_substrings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:36:27 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 10:07:50 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_arguments_and_redirections(t_substring **substring, \
char **remaining_line, t_command_line **command_line)
{
	int	status_code_redirections;
	int	status_code_arguments;

	status_code_redirections = 0;
	status_code_arguments = 0;
	while (*remaining_line[0] && *remaining_line[0] != '|')
	{
		if (*remaining_line[0] == '<' || *remaining_line[0] == '>')
		{
			status_code_redirections = get_redirections(remaining_line, \
			*substring, command_line);
			if (status_code_redirections != 0)
				return (status_code_redirections);
		}
		else
		{
			status_code_arguments = get_arguments(remaining_line, *substring, \
			command_line);
			if (status_code_arguments != 0)
				return (status_code_arguments);
		}
		*remaining_line = skip_first_whitespaces(*remaining_line);
	}
	return (0);
}

static int	parse_substrings(char **remaining_line, \
t_command_line **command_line, int susbtring_index)
{
	t_substring	*substring;
	int			status_code;	

	substring = NULL;
	status_code = 0;
	*remaining_line = skip_first_whitespaces(*remaining_line);
	if (ft_strlen(*remaining_line) == 0)
		return (0);
	if (is_pipe_first_character(*remaining_line) == true)
		return (2);
	init_substring_struct(&substring, command_line);
	status_code = get_arguments_and_redirections(&substring, remaining_line, \
	command_line);
	if (status_code == 2)
	{
		free_substring(&substring);
		return (2);
	}
	substring->substring_index = susbtring_index;
	ft_lst_add_back1(&(*command_line)->substrings, substring);
	return (0);
}

static int	cut_remaining_line_on_pipes(t_command_line **command_line, \
char *remaining_line)
{
	int	index;
	int	status_code;

	status_code = 0;
	index = 0;
	while (remaining_line[0])
	{
		status_code = parse_substrings(&remaining_line, command_line, index);
		if (status_code == 2)
		{
			(*command_line)->current_exit_code = 2;
			ft_putstr_fd("syntax error\n", 2);
			return (2);
		}
		remaining_line = skip_first_whitespaces(remaining_line);
		if (is_pipe_latest_character(&remaining_line) == true)
		{
			(*command_line)->current_exit_code = 2;
			ft_putstr_fd("syntax error\n", 2);
			return (2);
		}
		index++;
	}
	return (0);
}

t_command_line	*parse_command_line(char **argv, char *str, \
t_envp_struct **envp_struct, int previous_exit_code)
{
	t_command_line	*command_line;
	char			*remaining_line;
	int				status_code;

	command_line = NULL;
	status_code = 0;
	if (init_command_line_struct(&command_line) == -1)
	{
		free_envp_struct(envp_struct);
		error_allocation_command_line_and_exit(&command_line);
	}
	command_line->argv = argv;
	command_line->previous_exit_code = previous_exit_code;
	command_line->envp_struct = *envp_struct;
	remaining_line = skip_first_whitespaces(str);
	if (ft_strlen(remaining_line) == 0)
		return (command_line);
	status_code = cut_remaining_line_on_pipes(&command_line, remaining_line);
	if (status_code != 0)
		return (command_line);
	expand_contents(&command_line);
	return (command_line);
}
