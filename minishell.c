#include "minishell.h"

/*int main (void)
{
	int 		i;
	char 		*line;
	t_list		*list;
	t_element	*new_element;
	t_element	*element_to_del;
//	t_element	*parsing_result;

	i = 0;
	list_initialization(&list, 0);
	while (1)
	{
		line = readline("minishell : ");
		if (!line)
			break;
		add_history(line);//here?
	//	parsing_result = ft_parse_command_line(line);
		new_element = ft_lst_dc_new(line, NULL, NULL);
		ft_lst_dc_add_back(&list->head, new_element);
	
		i++;
	}
	ft_lst_dc_print(list->head);
	while (list->head)
	{
		element_to_del = list->head;
		ft_lst_dc_delone(&list->head, element_to_del);
	}
	free(list);
	return (0);
}*/

/*# include <term.h>
# include <termios.h>
# include <curses.h>
# include <stdio.h>

int main(void)
{

	char *bp = NULL; 
	char *term_type = getenv("TERM");
//	tgetent(char *bp, const char *name)
	tgetent(bp, term_type);
	printf("%s\n", bp);

}*/
int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp_struct	*envp_struct;
	t_command_line	*command_line;
	t_exec_struct	*exec_struct;
	int				previous_exit_code;
	int				exit_code;

	(void)argc;
	line = NULL;
	envp_struct = NULL;
	previous_exit_code = 0;
//	if (envp_struct)
//		ft_envp_struct_lst_print(envp_struct, 1);
	/*if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		ft_putstr_fd("line: ", STDERR_FILENO);
		ft_putstr_fd(line, STDERR_FILENO);
		write (STDERR_FILENO, "\n", 1);
		free(line);
		exit(0);
	}*/
/*	if (argc == 2)//for tests
	{
	 	int fd = ft_atoi(argv[1]);
		line = get_next_line(fd);
	}
	else if (!isatty(STDIN_FILENO))
		line = get_next_line(STDIN_FILENO);*/
	while (1)
	{
		get_envp(envp, &envp_struct, line);
		//if (isatty(STDIN_FILENO) && argc != 2)
			line = readline("minishell : ");
		if (!line)
		{
			free_envp_struct(&envp_struct);
			clear_history();
			break;
		}
		if (line[0])//no history on empty lines
			add_history(line);//here?
		if (ft_strncmp(line, "exit", 4) != 0)//pb free with exittt
		{
			command_line = parse_command_line(argv, line, &envp_struct, previous_exit_code);
//			if (command_line->exit_code != 0)
//				error_handling(&command_line);
		}
//		if (ft_strncmp(command_line->substrings->exp_arguments->content, "exit_code", 9) == 0)
/*		if (ft_strncmp(command_line->substrings->exp_arguments->content, "?", 1) == 0)
		{
			ft_putstr_fd("exit_code : ", 1);
			ft_putnbr_fd(command_line->exit_code, 1);
			ft_putstr_fd("\n", 1);
		}*/
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free_envp_struct(&envp_struct);
			free(line);
			line = NULL;
			clear_history();
			exit (EXIT_SUCCESS);
		}
		if (init_exec_struct(&exec_struct) == -1)
			error_allocation_exec_struct_and_exit(&exec_struct);
		exec_struct->envp_struct = envp_struct;
		exec_struct->command_line = command_line;
		if (command_line->substrings && command_line->current_exit_code == 0)
		{
			build_exec_struct(&exec_struct);
//			if (command_line->exit_code != 0)
//				error_handling(&command_line);
//			ft_execution_lst_print(exec_struct, 1);
			execution(&exec_struct);
		}
		if (command_line)
		{
			previous_exit_code = command_line->current_exit_code;
			exit_code = command_line->current_exit_code;
		}
		line = free_and_null(line);
		free_envp_struct(&envp_struct);
		free_all_command_line(&command_line);
		free_all_exec_struct(&exec_struct);
	}
	return (exit_code);//for script_test
}

