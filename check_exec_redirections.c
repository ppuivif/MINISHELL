#include "minishell.h"

static int	check_outfile(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection)
{
	if (exp_redirection->e_redirection == REDIRECTION_OUTFILE)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (exp_redirection->e_redirection == REDIRECTION_APPEND)
		(*exec_redirection)->fd_output = \
		open(exp_redirection->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->e_redirection = exp_redirection->e_redirection;
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
		if (access(exp_redirection->content, F_OK) == -1)
			perror(exp_redirection->content);
		else
			perror(exp_redirection->content);
		return_value = -2;
	}
	(*exec_redirection)->file = ft_strdup(exp_redirection->content);
	(*exec_redirection)->e_redirection = exp_redirection->e_redirection;
	return (return_value);
}

static int	check_heredoc(t_expanded_redirection *exp_redirection, \
t_exec_redirection **exec_redirection, t_envp_struct *envp_struct)
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
	limiter = ft_strjoin(exp_redirection->content, "\n");
	while (1)
	{
		line = get_next_line(0);
		if (ft_strcmp(line, limiter) == 0)
		{
			line = free_and_null(line);
			close(fd);
			break;
		}
		expand_content_when_heredoc(&line, envp_struct);
		ft_putstr_fd(line, fd);
		line = free_and_null(line);
	}
	free(limiter);
	limiter = NULL;
	(*exec_redirection)->file = filename;
	(*exec_redirection)->e_redirection = REDIRECTION_INFILE;
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
//	printf("fd_output : %d\n", (*exec_redirection)->fd_output);

	if ((exp_redirection->e_redirection == REDIRECTION_OUTFILE || \
	exp_redirection->e_redirection == REDIRECTION_APPEND) && \
	(*exec_substring)->is_previous_file_opened == true)
	{
		return_value = check_outfile(exp_redirection, exec_redirection);
		return (return_value);
	}
	else if (exp_redirection->e_redirection == REDIRECTION_INFILE && \
	(*exec_substring)->is_previous_file_opened == true)
	{
		return_value = check_infile(exp_redirection, exec_redirection);
		return (return_value);
	}
	if (exp_redirection->e_redirection == REDIRECTION_HEREDOC)
	{
		return_value = check_heredoc(exp_redirection, exec_redirection, exec_struct->envp_struct);
		return (return_value);
	}
	else
		return (-1);
}
