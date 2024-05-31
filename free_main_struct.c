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

static void	close_fd(int fd)
{
	if (fd && fd != -1 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}



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

static void	free_main_struct(t_main_struct **main_struct)
{
//	close_fd(main_struct->fd_input);
//	close_fd(main_struct->fd_output);
	/*while (main_struct->head != NULL)
		ft_lst_dc_delone(&main_struct->head, main_struct->head);*/
	
	
	
	if (*main_struct)
		free(*main_struct);
}


static void	free_command(t_command **commands)
{
	t_command	*tmp;

	while (ft_lst_size9(*commands))
	{
		tmp = (*commands)->next;
		free((*commands)->cmd_arr);
		free((*commands)->path);
		free(*commands);
		*commands = tmp;
	}
}

static void	free_redirection(t_redirection **redirections)
{
	t_redirection	*tmp;

	while (ft_lst_size8(*redirections))
	{
		tmp = (*redirections)->next;
		free ((*redirections)->file);
		free (*redirections);
		*redirections = tmp;
	}
}

static void	free_execution(t_execution **executions)
{
	t_execution	*tmp;

	while (ft_lst_size7(*executions))
	{
		tmp = (*executions)->next;
		if ((*executions)->redirections)
			free_redirection(&(*executions)->redirections);
		if ((*executions)->commands)
			free_command(&(*executions)->commands);
		free ((*executions)->redirections);
		free ((*executions)->commands);
		free ((*executions));
		*executions = tmp;
	}
}

void	free_all_main_struct(t_main_struct **main_struct)
{
	if (*main_struct)
	{
		if ((*main_struct)->executions)
			free_execution(&(*main_struct)->executions);
		free_main_struct(main_struct);
	}
}


