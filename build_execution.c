#include "minishell.h"


void	build_exec_struct(t_command_line **command_line, t_exec_struct **exec_struct)
{
	t_substring	*tmp;

	tmp = (*command_line)->substrings;
	while (tmp)
	{
		build_exec_subline_struct(tmp, command_line, exec_struct);
		tmp = tmp->next;
	}
}

void	build_exec_subline_struct(t_substring *substring, t_command_line **command_line, t_exec_struct **exec_struct)
{
	t_exec_subline			*exec_subline;
	t_expanded_redirection	*tmp1;
	t_expanded_argument		*tmp2;

	if (init_exec_subline_struct(&exec_subline) == -1)
		error_allocation_exec_struct(exec_struct, command_line);
	tmp1 = substring->exp_redirections;
	tmp2 = substring->exp_arguments;
	while (tmp1)
	{
		build_exec_redirection_struct(tmp1, &exec_subline, command_line, exec_struct);
//		if ((*command_line)->exit_code != 0)//code to find when file couldn't be opened
//			return ;
		tmp1 = tmp1->next;
	}		
	while (tmp2)
	{
		build_exec_argument_struct(tmp2, &exec_subline, command_line, exec_struct);
//		if ((*command_line)->exit_code != 0)//code to find when cmd or arg doesn't exist
//			return ;
		tmp2 = tmp2->next;
	}
//	check_commands(&exec_subline, command_line, exec_struct);
//	check_commands(command_line, exec_struct);

	ft_lst_add_back7(&(*exec_struct)->exec_sublines, exec_subline);
}

void	build_exec_redirection_struct(t_expanded_redirection *exp_redirections, t_exec_subline **exec_subline, t_command_line **command_line, t_exec_struct **exec_struct)
{
	t_exec_redirection		*exec_redirection;
	t_expanded_redirection *tmp;

	if (init_exec_redirection_struct(&exec_redirection) == -1)
		error_allocation_exec_struct(exec_struct, command_line);
	tmp = exp_redirections;
	while (tmp)
	{
		exec_redirection->file = tmp->content;
		exec_redirection->e_redirection = tmp->e_redirection;
		(*command_line)->exit_code = open_and_check_file(tmp, &exec_redirection);
		if ((*command_line)->exit_code != 0)//code to find when file couldn't be opened
			return ;
		tmp = tmp->next;
	}
	ft_lst_add_back8(&(*exec_subline)->exec_redirections, exec_redirection);
}

void	build_exec_argument_struct(t_expanded_argument *exp_arguments, t_exec_subline **exec_subline, t_command_line **command_line, t_exec_struct **exec_struct)
{
	t_exec_argument			*exec_argument;
	t_expanded_argument *tmp;

	if (init_exec_argument_struct(&exec_argument) == -1)
		error_allocation_exec_struct(exec_struct, command_line);
	tmp = exp_arguments;
	while (tmp)
	{
		exec_argument->argument = tmp->content;
		tmp = tmp->next;
	}
	ft_lst_add_back9(&(*exec_subline)->exec_arguments, exec_argument);
}


//		(*command_line)->exit_code = check_command(tmp, command, (*exec_struct)->envp);
//		if ((*command_line)->exit_code != 0)//code to find when file couldn't be opened
//			return ;
