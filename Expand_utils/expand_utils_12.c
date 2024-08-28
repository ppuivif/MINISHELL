/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/28 15:18:05 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assignment_ambiguous_redirection( \
t_expanded_redirection *exp_redirection, t_exec_redirection **exec_redirection)
{
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	(*exec_redirection)->fd_output = -1;
	(*exec_redirection)->fd_input = -1;
	ft_putstr_fd(exp_redirection->content, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	return (1);
}

int	check_outfile(t_expanded_redirection *exp_redirection, \
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

int	check_infile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	int	return_value;

	return_value = 0;
	(*exec_redirection)->fd_input = open(exp_redirection->content, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		if (access(exp_redirection->content, F_OK) == -1)
			perror(exp_redirection->content);
		else
			perror(exp_redirection->content);
		return_value = 1;
	}
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->t_redirection = exp_redirection->t_redirection;
	return (return_value);
}

static int	read_and_expand_heredoc(t_expanded_redirection *exp_redirection, \
char **filename, int fd, t_command_line **command_line)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("heredoc : ");
		signals(1);
		if (g_sign)
		{
//			printf("voici le sign : %d\n", g_sign);//to delete
			unlink(*filename); // Optionally delete the temporary file
			*filename = free_and_null(*filename);
			return (1);
		}
		if (!line || ft_strcmp(line, exp_redirection->content) == 0)
			break ;
		if (line[0])
			add_history(line);
		expand_content_when_heredoc(&line, command_line, \
		exp_redirection->flag_for_expand);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		line = free_and_null(line);
	}
	line = free_and_null(line);
	return (0);
}

int	check_heredoc(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_command_line **command_line)
{
	int		fd;
	char	*filename;
	char	*index;

	index = ft_itoa((*exec_redirection)->substring_index);
	filename = ft_strjoin("heredoc_tmp_", index);
	index = free_and_null(index);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	if (read_and_expand_heredoc(exp_redirection, &filename, fd, command_line))
	{
		close(fd);
		return (1);
	}
	close(fd);
	(*exec_redirection)->file = filename;
	(*exec_redirection)->t_redirection = REDIRECTION_INFILE;
	(*exec_redirection)->fd_input = open((*exec_redirection)->file, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		perror((*exec_redirection)->file);
		return (1);
	}
	return (0);
}
