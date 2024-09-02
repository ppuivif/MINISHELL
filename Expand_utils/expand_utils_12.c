/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/02 11:58:19 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_file_in_heredoc(t_expanded_redirection *exp_redirection, \
t_command_line **command_line, char **line, int fd)
{
		if (line[0])
			add_history(*line);
		expand_content_when_heredoc(line, command_line, \
		exp_redirection->flag_for_expand);
		ft_putstr_fd(*line, fd);
		ft_putstr_fd("\n", fd);
}

static int	heredoc_assignation(t_exec_redirection **exec_redirection, \
char *filename, int status_code)
{
	(*exec_redirection)->file = filename;
	(*exec_redirection)->t_redirection = REDIRECTION_INFILE;
	if (status_code == 130 || status_code == 131)
	{
		(*exec_redirection)->fd_input = -1;
		return (status_code);
	}
	(*exec_redirection)->fd_input = open((*exec_redirection)->file, O_RDONLY);
	if ((*exec_redirection)->fd_input == -1)
	{
		perror((*exec_redirection)->file);
		return (1);
	}
	return (0);
}

static int	read_and_expand_heredoc(t_expanded_redirection *exp_redirection, \
int fd, t_command_line **command_line)
{
	char	*line;

	line = NULL;
	while (1)
	{
		signals(1);
		if (g_sign)
		{
			g_sign = 0;
			return (128 + g_sign);
		}
		line = readline("heredoc : ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document at line \
delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strcmp(line, exp_redirection->content) == 0)
			break ;
		fill_file_in_heredoc(exp_redirection, command_line, &line, fd);
		line = free_and_null(line);
	}
	line = free_and_null(line);
	return (0);
}

int	check_heredoc(t_exec_struct **exec_struct, \
t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	int		fd;
	char	*filename;
	char	*index;
	int		status_code;

	index = ft_itoa((*exec_redirection)->substring_index);
	filename = ft_strjoin("heredoc_tmp_", index);
	index = free_and_null(index);
	status_code = 0;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	status_code = read_and_expand_heredoc(exp_redirection, fd, \
	&(*exec_struct)->command_line);
	close(fd);
	if (status_code == 1)
		return (1);
	status_code = heredoc_assignation(exec_redirection, filename, \
	status_code);
	return (status_code);
}
