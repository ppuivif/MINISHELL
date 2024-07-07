#include "minishell.h"

int	get_arguments(char **remaining_line, t_substring *substring, \
t_command_line **command_line)
{
	int					len;
	t_native_argument	*n_argument;

	len = 0;
	n_argument = NULL;
	*remaining_line = skip_first_whitespaces(*remaining_line);
	len = count_len_to_cut(*remaining_line);
	if (len == -1)
		return (2);//syntax_error
	if (init_native_argument_struct(&n_argument) == -1)
		error_allocation_command_line_and_exit(command_line);
	n_argument->content = ft_substr(*remaining_line, 0, len);
	if (!n_argument->content)
	{
		n_argument = free_and_null(n_argument);
		error_allocation_command_line_and_exit(command_line);
	}
	*remaining_line += len;
	ft_lst_add_back3(&substring->n_arguments, n_argument);
	return (0);
}
