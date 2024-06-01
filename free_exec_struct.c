#include "includes/linked_list_utils.h"

/*static void	free_cmd(t_cmd *cmd)
{
	if((cmd)->cmd_arr)
		free_arr((cmd)->cmd_arr);
	if((cmd)->path)
	{
		free((cmd)->path);
		(cmd)->path = NULL;
	}
	free(cmd);	
}*/

/*static void	close_fd(int fd)
{
	if (fd && fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}*/



/*void	free_arr(char **str_arr)
{
	int	i;

	i = 0;
	while ((str_arr)[i])
	{
		free(str_arr[i]);
		i++;
	}
	if (str_arr)
		free(str_arr);
	str_arr = NULL;
}*/

static void	free_exec_struct(t_exec_struct **exec_struct)
{
//	close_fd(main_struct->fd_input);
//	close_fd(main_struct->fd_output);
	/*while (main_struct->head != NULL)
		ft_lst_dc_delone(&main_struct->head, main_struct->head);*/
	
	
	
	if (*exec_struct)
		free(*exec_struct);
}


static void	free_exec_argument_struct(t_exec_argument **exec_arguments)
{
	t_exec_argument	*tmp;

	while (ft_lst_size9(*exec_arguments))
	{
		tmp = (*exec_arguments)->next;
		free((*exec_arguments)->cmd_arr);
		free((*exec_arguments)->path);
		free(*exec_arguments);
		*exec_arguments = tmp;
	}
}

static void	free_exec_redirection_struct(t_exec_redirection **exec_redirections)
{
	t_exec_redirection	*tmp;

	while (ft_lst_size8(*exec_redirections))
	{
		tmp = (*exec_redirections)->next;
		free ((*exec_redirections)->file);
		free (*exec_redirections);
		*exec_redirections = tmp;
	}
}

static void	free_exec_subline_struct(t_exec_subline **exec_sublines)
{
	t_exec_subline	*tmp;

	while (ft_lst_size7(*exec_sublines))
	{
		tmp = (*exec_sublines)->next;
		if ((*exec_sublines)->exec_redirections)
			free_exec_redirection_struct(&(*exec_sublines)->exec_redirections);
		if ((*exec_sublines)->exec_arguments)
			free_exec_argument_struct(&(*exec_sublines)->exec_arguments);
		free ((*exec_sublines)->exec_redirections);
		free ((*exec_sublines)->exec_arguments);
		free ((*exec_sublines));
		*exec_sublines = tmp;
	}
}

void	free_all_exec_struct(t_exec_struct **exec_struct)
{
	if (*exec_struct)
	{
		if ((*exec_struct)->exec_sublines)
			free_exec_subline_struct(&(*exec_struct)->exec_sublines);
		free_exec_struct(exec_struct);
	}
}


