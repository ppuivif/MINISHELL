#include "minishell.h"

void	error_allocation_envp_struct_and_exit(void)
{
	ft_putstr_fd("error\nan allocation failed\n", 2);
	exit(EXIT_FAILURE);
}

void	error_allocation_exec_struct_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	error_allocation_command_line_and_exit(&(*exec_struct)->command_line,
		&(*exec_struct)->envp_struct);
}

void	error_allocation_command_line_and_exit(t_command_line **command_line, \
t_envp_struct **envp_struct)
{
	free_envp(envp_struct);
	free_all_command_line(command_line);
	ft_putstr_fd("error\nan allocation failed\n", 2);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_handling(t_command_line *command_line)
{
	int	exit_code;

	exit_code = command_line->current_exit_code;
	if (exit_code == 1)
		ft_putstr_fd("error\n", 2);
	if (exit_code == 2)
		ft_putstr_fd("syntax error\n", 2);
//	exit (exit_code);// for script.sh
}
