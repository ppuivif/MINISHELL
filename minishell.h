#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "includes/libft_utils.h"
# include "includes/linked_list_utils.h"

# include <stdio.h>//to delete














void			print_arr(char **arr);
t_command_line 	*parse_command_line(char *str);
int		parse_substrings(char **remaining_line, t_command_line *command_line);
int		get_redirections(char **remaining_line, t_substring *substring);
int		get_arguments(char **remaining_line, t_substring *substring);

int		init_argument_struct(t_native_argument **n_argument);
int		init_redirection_struct(t_native_redirection **n_redirection);
int		init_substring_struct(t_substring **substring);
int		init_command_line_struct(t_command_line **command_line);

void	error_allocation(t_command_line **command_line);

#endif