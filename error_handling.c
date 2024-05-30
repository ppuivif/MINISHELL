#include "minishell.h"

void	error_allocation(t_command_line **command_line)
{
	free_all(command_line);
	ft_putstr_fd("error\nan allocation failed\n", 2);
	clear_history();
	exit(EXIT_FAILURE);
}

void   error_handling(t_command_line **command_line)
{
    int exit_code;

    exit_code = (*command_line)->exit_code;
    if (exit_code == 1)
        ft_putstr_fd("error\n", 2);
    if (exit_code == 2)
        ft_putstr_fd("syntax error\n", 2);
    free_all(command_line);
//	clear_history();
 //   exit(exit_code);//exit or return ?
//	return (exit_code);

}