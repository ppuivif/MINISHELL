/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:46 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 17:12:15 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_sign = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static int	check_outfile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	if (exp_redirection->t_redirection == REDIRECTION_OUTFILE)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (exp_redirection->t_redirection == REDIRECTION_APPEND)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	if ((*exec_redirection)->fd_output == -1)
	{
		perror(exp_redirection->content);
		return (1);
	}
	return (0);
}

static int	check_infile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	int	return_value;

	return_value = 0;
	(*exec_redirection)->fd_input = open(exp_redirection->content, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		if (access(exp_redirection->content, F_OK) == -1) //voir plutot stat
			perror(exp_redirection->content);
		else
			perror(exp_redirection->content);
		return_value = -2;
	}
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	return (return_value);
}

static int	check_heredoc(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_command_line **command_line)
{
	char	*line;
	int		fd;
	char	*limiter;
	char	*filename;
	char	*index;

	line = NULL;
	index = ft_itoa((*exec_redirection)->substring_index);
	filename = ft_strjoin("heredoc_tmp_", index);
	free (index);
	index = NULL;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	limiter = exp_redirection->content;
//	limiter = ft_strjoin(exp_redirection->content, "\n");
	while (1)
	{
		line = readline("heredoc : ");
		signals(1);
		if (g_sign)
		{
//          rl_clear_history();
//			printf("voici le sign : %d\n", g_sign);//to delete
			close(fd);
			unlink(filename); // Optionally delete the temporary file
			free(filename);
			return (-1);
		}
		if (!line)
		{
//			rl_clear_history();
			close(fd);
			break ;
		}
		if (ft_strcmp(line, limiter) == 0)
		{
			line = free_and_null(line);
			close(fd);
			break ;
		}
		if (line[0])
			add_history(line);
		expand_content_when_heredoc(&line, command_line, \
		exp_redirection->flag_for_expand);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		line = free_and_null(line);
	}
//	free(limiter);
//	limiter = NULL;
	(*exec_redirection)->file = filename;
	(*exec_redirection)->t_redirection = REDIRECTION_INFILE;
	(*exec_redirection)->fd_input = open((*exec_redirection)->file, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		perror((*exec_redirection)->file);
		return (-1);
	}
	return (0);
}

int	open_and_check_file(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_exec_substring **exec_substring, \
t_exec_struct *exec_struct)
{
	int	return_value;

	return_value = 0;
//	printf("fd_input : %d\n", (*exec_redirection)->fd_input);
	if ((exp_redirection->t_redirection == REDIRECTION_OUTFILE || \
	exp_redirection->t_redirection == REDIRECTION_APPEND) && \
	(*exec_substring)->is_previous_file_opened == true)
	{
		return_value = check_outfile(exp_redirection, exec_redirection);
		return (return_value);
	}
	else if (exp_redirection->t_redirection == REDIRECTION_INFILE && \
	(*exec_substring)->is_previous_file_opened == true)
	{
		return_value = check_infile(exp_redirection, exec_redirection);
		return (return_value);
	}
	if (exp_redirection->t_redirection == REDIRECTION_HEREDOC)
	{
		return_value = check_heredoc(exp_redirection, exec_redirection, \
		&exec_struct->command_line);
		return (return_value);
	}
	else
		return (-1);
}
