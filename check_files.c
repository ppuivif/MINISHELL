#include "minishell.h"

int	check_list_of_files(t_command_line **command_line, t_main_struct *main_struct)
{
	t_substring		*tmp;

	tmp = (*command_line)->substrings;
	while (tmp)
	{
		if ( open_and_check_each_file(tmp, &main_struct, command_line) != 0)
			error_handling;


		
		tmp = tmp->next;
	}
}


int	open_and_check_each_file(t_substring tmp , t_main_struct **main_struct, t_command_line **command_line)
{
	t_main_struct	*new_element;

	if (init_main_struct(new_element) == -1)
		error_allocation_main_struct(main_struct, command_line)

	new_element->file =  
	
	= open(argv[main_struct->nb_arg], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (main_struct->fd_output == -1)
		{
			perror("error\noutfile couldn't be opened");
			error_handling(main_struct);
		}
		if (ft_strncmp(argv[1], "here_doc", 8) != 0)
		{
			main_struct->fd_input = open(argv[1], O_RDONLY);
			if (main_struct->fd_input == -1)
			{
				if (access(argv[1], F_OK) == -1)
					perror("error\ninfile doesn't exist");
				else
					perror("error\ninfile couldn't be opened");
			}
		}
		else
		{
//			read_here_doc(argv)
		}


}
