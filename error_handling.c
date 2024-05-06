#include "minishell.h"

void	error_allocation(t_command_line **command_line)
{
	free_all(command_line);
	ft_putstr_fd("error\nan allocation failed\n", 2);
	exit(EXIT_FAILURE);
}
