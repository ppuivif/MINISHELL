/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:36:12 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 17:10:53 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sign = 0;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_envp_struct	*envp_struct;
	t_command_line	*command_line;
	t_exec_struct	*exec_struct;
	int				previous_exit_code;
	int				exit_code;
	int				fd;

//	(void)argc;//for tests
//	(void)argv;//for tests
	line = NULL;
	envp_struct = NULL;
	previous_exit_code = 0;
	exit_code = 0;
/*	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		ft_putstr_fd("line: ", STDERR_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		write (STDERR_FILENO, "\n", 1);
		free(line);
		exit(0);
	}*/
	if (argc == 2) //for tests
	{
		fd = ft_atoi(argv[1]);
		line = get_next_line(fd);
	}
	get_envp(envp, &envp_struct, line);
/*	if (envp_struct)
		ft_envp_struct_lst_print(envp_struct, 1);*/
	while (1)
	{
//		if (isatty(STDIN_FILENO))
		signals(0);
		if (argc != 2)
			line = readline("minishell : ");
		if (!line)
		{
			free_envp_struct(&envp_struct);
			rl_clear_history();
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (g_sign == 2)
			exit_code = 130;//or 128+2=130
		else if (g_sign == 3)
			exit_code = 131;//or 128+3=131
		g_sign = 0;
		if (exit_code != 0)
			previous_exit_code = exit_code;
		if (line[0]) //no history on empty lines
		{
			add_history(line);//here?
			command_line = parse_command_line(argv, line, \
			&envp_struct, previous_exit_code);
			if (init_exec_struct(&exec_struct) == -1)
				error_allocation_exec_struct_and_exit(&exec_struct);
			exec_struct->envp_struct = envp_struct;
			exec_struct->command_line = command_line;
			if (command_line->substrings && \
			command_line->current_exit_code == 0)
			{
				build_exec_struct(&exec_struct);
				signals(1);
//				ft_execution_lst_print(exec_struct, 1);
				execution(&exec_struct);
				envp_struct = exec_struct->envp_struct;
			}
			//printf("%d\n", exit_code);
			if (command_line)
			{
				previous_exit_code = command_line->current_exit_code;
				exit_code = command_line->current_exit_code;
			}
			line = free_and_null(line);
			free_all_command_line(&command_line);
			free_all_exec_struct(&exec_struct);
		}
	}
	free_envp_struct(&envp_struct);
	return (exit_code);
}
