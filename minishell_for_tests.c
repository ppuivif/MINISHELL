/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_for_tests.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:36:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 22:27:42 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sign = 0;

static void save_exit_code_and_free_lists(t_exec_struct **exec_struct, \
char *line, int *exit_code)
{
	if ((*exec_struct)->command_line)
		*exit_code = (*exec_struct)->command_line->current_exit_code;
	free(line);
	free_all_command_line(&(*exec_struct)->command_line);
	free_all_exec_struct(exec_struct);
	g_sign = 0;
}

static void	init_and_execute(t_exec_struct **exec_struct, \
t_command_line *command_line, t_envp_struct **envp_struct)
{
	if (init_exec_struct(exec_struct) == -1)
		error_allocation_exec_struct_and_exit(exec_struct);
	(*exec_struct)->envp_struct = *envp_struct;
	(*exec_struct)->command_line = command_line;
	if (command_line->substrings && \
	command_line->current_exit_code == 0)
	{
		build_exec_struct(exec_struct);
		if (command_line->current_exit_code != 130)
		{
			signals(2);
//			ft_execution_lst_print(exec_struct, 1);
			execution(exec_struct);
			*envp_struct = (*exec_struct)->envp_struct;
		}
	}
}

static void	readline_and_get_signals(t_envp_struct **envp_struct, char **line, \
int *exit_code)
{
	signals(0);
	if (!(*line))
	{
		free_envp_struct(envp_struct);
		rl_clear_history();
		ft_putstr_fd("exit\n", 2);
		return ;
	}
	if (g_sign)
		*exit_code = 128 + g_sign;
	g_sign = 0;
}

static void	get_command_line(t_envp_struct **envp_struct, char **line, \
int *exit_code, char **argv)
{
	t_command_line	*command_line;
	t_exec_struct	*exec_struct;
	int				previous_exit_code;

	command_line = NULL;
	exec_struct = NULL;
	previous_exit_code = 0;
	while (1)
	{
		readline_and_get_signals(envp_struct, line, exit_code);
		if (!*line)
			break;
		previous_exit_code = *exit_code;
		if (*line[0])
		{
			add_history(*line);
			command_line = parse_command_line(argv, *line, \
			envp_struct, previous_exit_code);
			init_and_execute(&exec_struct, command_line, envp_struct);
			save_exit_code_and_free_lists(&exec_struct, *line, exit_code);
			*line = NULL;
		}
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)//for tests
{
	int				fd;
	char			*line;
	t_envp_struct	*envp_struct;
	int				exit_code;

	line = NULL;
	envp_struct = NULL;
	exit_code = 0;
	get_envp(envp, &envp_struct);
	if (argc == 2)
	{
		fd = ft_atoi(argv[1]);
		line = get_next_line(fd);
	}
	get_command_line(&envp_struct, &line, &exit_code, argv);
	free_envp_struct(&envp_struct);
	return (exit_code);
}
