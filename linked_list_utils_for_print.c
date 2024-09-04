/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils_for_print.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:36 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/23 14:31:07 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list_utils.h"//file to delete

void	ft_envp_struct_lst_print(t_envp_struct *envp_struct, int fd)
{
	size_t			i;
	t_envp_struct	*tmp;

	i = 0;
	tmp = envp_struct;
	while (tmp && i < ft_lst_size6(envp_struct))
	{
		ft_putstr_fd("envp[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("] : ", fd);
		ft_putstr_fd(tmp->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(tmp->value, fd);
//		ft_putstr_fd(envp_struct->content, fd);
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
//		envp_struct = envp_struct->next;
		i++;
	}
}

void	ft_native_lst_print(t_command_line *command_line, int fd)
{
	size_t					i;
	size_t					j;
	t_substring				*tmp1;
	t_native_redirection	*tmp2;
	t_native_argument		*tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->n_redirections;
		while (tmp1->n_redirections && j < ft_lst_size2(tmp1->n_redirections))
		{
			ft_putstr_fd("\t-n_redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-n_redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_t_redirection (tmp2->t_redirection, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->n_arguments;
		while (tmp1->n_arguments && j < ft_lst_size3(tmp1->n_arguments))
		{
			ft_putstr_fd("\t-n_argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	ft_native_lst_print_for_tests(t_command_line *command_line, int fd)
{
	size_t					i;
	size_t					j;
	t_substring				*tmp1;
	t_native_redirection	*tmp2;
	t_native_argument		*tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->n_redirections;
		while (tmp1->n_redirections && j < ft_lst_size2(tmp1->n_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_t_redirection (tmp2->t_redirection, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->n_arguments;
		while (tmp1->n_arguments && j < ft_lst_size3(tmp1->n_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	ft_expanded_lst_print(t_command_line *command_line, int fd)
{
	size_t					i;
	size_t					j;
	t_substring				*tmp1;
	t_expanded_redirection	*tmp2;
	t_expanded_argument		*tmp3;

	i = 0;
	tmp1 = command_line->substrings;
	while (command_line->substrings && i < ft_lst_size1(command_line->substrings))
	{
		ft_putstr_fd("substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exp_redirections;
		while (tmp1->exp_redirections && j < ft_lst_size4(tmp1->exp_redirections))
		{
			ft_putstr_fd("\t-exp_redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->content, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-exp_redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_t_redirection (tmp2->t_redirection, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exp_arguments;
		while (tmp1->exp_arguments && j < ft_lst_size5(tmp1->exp_arguments))
		{
			ft_putstr_fd("\t-exp_argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->content, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	ft_execution_lst_print(t_exec_struct *exec_struct, int fd)
{
	size_t				i;
	size_t				j;
	t_exec_substring	*tmp1;
	t_exec_redirection	*tmp2;
	t_exec_argument		*tmp3;

	i = 0;
	tmp1 = exec_struct->exec_substrings;
	while (exec_struct->exec_substrings && i < ft_lst_size7(exec_struct->exec_substrings))
	{
		ft_putstr_fd("exec_substring ", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd(" : \n", fd);
		j = 0;
		tmp2 = tmp1->exec_redirections;
		while (tmp1->exec_redirections && j < ft_lst_size8(tmp1->exec_redirections))
		{
			ft_putstr_fd("\t-redirection ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			ft_putstr_fd(tmp2->file, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-redirection_type ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t", fd);
			print_t_redirection (tmp2->t_redirection, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_input ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_input, fd);
			ft_putstr_fd("\n", fd);
			ft_putstr_fd("\t-fd_output ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : \t\t", fd);
			ft_putnbr_fd(tmp2->fd_output, fd);
			ft_putstr_fd("\n", fd);
			tmp2 = tmp2->next;
			j++;
		}
		j = 0;
		tmp3 = tmp1->exec_arguments;
		while (tmp1->exec_arguments && j < ft_lst_size9(tmp1->exec_arguments))
		{
			ft_putstr_fd("\t-argument ", fd);
			ft_putnbr_fd(j, fd);
			ft_putstr_fd(" : ", fd);
			ft_putstr_fd(tmp3->argument, fd);
			ft_putstr_fd("\n", fd);
			tmp3 = tmp3->next;
			j++;
		}
		ft_putstr_fd("\n", fd);
		tmp1 = tmp1->next;
		i++;
	}
}

void	print_t_redirection(int t_redirection, int fd)
{
	if (t_redirection == 0)
		ft_putstr_fd("REDIRECTION_OUTFILE", fd);
	if (t_redirection == 1)
		ft_putstr_fd("REDIRECTION_INFILE", fd);
	if (t_redirection == 2)
		ft_putstr_fd("REDIRECTION_INDEFINED", fd);
	if (t_redirection == 3)
		ft_putstr_fd("REDIRECTION_APPEND", fd);
	if (t_redirection == 4)
		ft_putstr_fd("REDIRECTION_HEREDOC", fd);
	if (t_redirection == 5)
		ft_putstr_fd("REDIRECTION_TEXT", fd);
}
