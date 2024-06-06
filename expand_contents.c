#include "minishell.h"

void	expand_contents(t_command_line **command_line)
{
	t_substring				*tmp1;
	t_native_redirection	*tmp2;
	t_native_argument		*tmp3;

	tmp1 = (*command_line)->substrings;
	while (tmp1)
	{
		tmp2 = tmp1->n_redirections;
		//while (tmp2)
		while (tmp2 && (*command_line)->current_exit_code == 0)
		{
			expand_redirections(tmp1, tmp2, command_line);
			if (tmp1->exp_redirections->alloc_succeed == false)
				free_all_command_line(command_line);
			tmp2 = tmp2->next;
		}
		tmp3 = tmp1->n_arguments;
		while (tmp3 && (*command_line)->current_exit_code == 0)
		//while (tmp3)
		{
			expand_arguments(tmp1, tmp3, command_line);
			if (tmp1->exp_arguments->alloc_succeed == false)
				free_all_command_line(command_line);
			tmp3 = tmp3->next;
		}
		tmp1 = tmp1->next;
	}
}
