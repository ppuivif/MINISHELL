#include "minishell.h"

void	error_allocation_envp_struct_and_exit(void)
{
	ft_putstr_fd("error : an allocation failed\n", 2);
	exit(EXIT_FAILURE);
}

void	error_allocation_exec_struct_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	error_allocation_command_line_and_exit(&(*exec_struct)->command_line);
}

void	error_allocation_command_line_and_exit(t_command_line **command_line)
{
	free_envp_struct(&(*command_line)->envp_struct);
	free_all_command_line(command_line);
	ft_putstr_fd("error : an allocation failed\n", 2);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_pipe_creation_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	ft_putstr_fd("error : a pipe creation failed\n", 2);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_fork_creation_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	ft_putstr_fd("error : a fork creation failed\n", 2);
	clear_history();
	exit(EXIT_FAILURE);
}

void	error_execve_and_exit(t_exec_struct **exec_struct)
{
	free_all_exec_struct(exec_struct);
	free_envp_struct(&(*exec_struct)->envp_struct);
	free_all_command_line(&(*exec_struct)->command_line);
	ft_putstr_fd("error\nexecve of a cmd failed", 2);
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
