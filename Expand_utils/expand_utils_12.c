/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_12.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:06 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/02 18:00:24 by ppuivif          ###   ########.fr       */
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

static int	exp_redirec_modif(t_expanded_redirection **exp_redirection, \
char *filename, int status_code)
{
	(*exp_redirection)->content = free_and_null((*exp_redirection)->content);
	(*exp_redirection)->content = filename;
	(*exp_redirection)->t_redirection = REDIRECTION_INFILE;
	if (status_code == 130 || status_code == 131)
		return (status_code);
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
			return (128 + g_sign);
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


static char	*create_heredoc_file_name(t_substring *substring, \
t_expanded_redirection **exp_redirection, t_command_line **command_line)
{
	char	*filename;
	char	*substring_index;
	char	*exp_redirection_index;
	(void)command_line;

	substring_index = ft_itoa(substring->substring_index);
//	malloc protection
	exp_redirection_index = ft_itoa((*exp_redirection)->exp_redirection_index);
//	malloc protection
	filename = ft_strjoin("heredoc_tmp_", substring_index);
//	malloc protection
	filename = ft_strjoin_freed(filename, "_");
//	malloc protection
	filename = ft_strjoin_freed(filename, exp_redirection_index);
//	malloc protection
	return (filename);
}


int	open_and_check_heredoc(t_substring *substring, \
t_expanded_redirection **exp_redirection, t_command_line **command_line)
{
	int		fd;
	char	*filename;
	int		status_code;

	filename = create_heredoc_file_name(substring, \
	exp_redirection, command_line);
	status_code = 0;
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	status_code = read_and_expand_heredoc(*exp_redirection, fd, \
	command_line);
	close(fd);
	if (status_code == 1)
		return (1);
	status_code = exp_redirec_modif(exp_redirection, filename, \
	status_code);
	return (status_code);
}
