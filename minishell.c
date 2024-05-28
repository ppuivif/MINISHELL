#include "minishell.h"

/*int main (void)
{
	int 		i;
	char 		*line;
	t_list		*list;
	t_element	*new_element;
	t_element	*element_to_del;
//	t_element	*parsing_result;

	i = 0;
	list_initialization(&list, 0);
	while (1)
	{
		line = readline("minishell : ");
		if (!line)
			break;
		add_history(line);//here?
	//	parsing_result = ft_parse_command_line(line);
		new_element = ft_lst_dc_new(line, NULL, NULL);
		ft_lst_dc_add_back(&list->head, new_element);
	
		i++;
	}
	ft_lst_dc_print(list->head);
	while (list->head)
	{
		element_to_del = list->head;
		ft_lst_dc_delone(&list->head, element_to_del);
	}
	free(list);
	return (0);
}*/

/*# include <term.h>
# include <termios.h>
# include <curses.h>
# include <stdio.h>

int main(void)
{

	char *bp = NULL; 
	char *term_type = getenv("TERM");
//	tgetent(char *bp, const char *name)
	tgetent(bp, term_type);
	printf("%s\n", bp);

}*/

int main(int argc, char **argv)
{
	char	*line;
	t_command_line *command_line;

	line = NULL;
	if (argc == 2)
	{
		while (1)
		{
			line = readline("minishell : ");
			if (!line)
				break;
			if (line[0])//no history on empty lines
				add_history(line);//here?
//			command_line = parse_command_line(line);
			command_line = parse_command_line(line, atoi(argv[1]));//to run script.sh
			free(line);
			line = NULL;
			if (command_line->exit_code != 0)
				return(error_handling(&command_line));
			free_all(&command_line);

		}
	}
	else
		ft_putstr_fd("please, give an fd to display\n", 1);
	return (0);
}