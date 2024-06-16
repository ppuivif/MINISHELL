

static int main(int argc, char **argv, char **envp)//for tests
{
	char	*line;
	t_envp_struct	*envp_struct;
	t_command_line	*command_line;
	t_exec_struct	*exec_struct;
	int				previous_exit_code;

	(void)argc;
	line = NULL;
	envp_struct = NULL;
	previous_exit_code = 0;
//	if (argc == 2)
//	{
		if (!isatty(STDIN_FILENO))
			line = get_next_line(STDIN_FILENO);
		while (1)
		{
			get_envp(envp, &envp_struct, line);
			if (isatty(STDIN_FILENO))
				line = readline("minishell : ");
			if (!line)
					break;
			if (line[0])//no history on empty lines
				add_history(line);//here?
			if (ft_strncmp(line, "exit", 4) != 0)//pb free with exittt
				command_line = parse_command_line(argv, line, &envp_struct, previous_exit_code);
			if (init_exec_struct(&exec_struct) == -1)
				error_allocation_exec_struct_and_exit(&exec_struct);
			exec_struct->envp_struct = envp_struct;
			exec_struct->command_line = command_line;
			if (command_line->substrings && command_line->current_exit_code != 2)
			{
				build_exec_struct(&exec_struct);
				execution(&exec_struct);
			}
			if (command_line)
				previous_exit_code = command_line->current_exit_code;
			free_and_null(line);
			free_envp_struct(&envp_struct);
			free_all_command_line(&command_line);
			free_all_exec_struct(&exec_struct);
		}
//	}
//	else
//		ft_putstr_fd("please, give an fd to display\n", 1);
	return (0);
}
