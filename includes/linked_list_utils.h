#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft_utils.h"

# include <stdio.h>//to delete

typedef struct s_native_argument t_native_argument;
typedef struct s_native_argument
{
	char				*content;
	t_native_argument	*next;
}	t_native_argument;

typedef struct s_native_redirection t_native_redirection;
typedef struct s_native_redirection
{
	char					*content;
	enum
	{
		REDIRECTION_OUTFILE = 0,
		REDIRECTION_INFILE = 1,
		REDIRECTION_APPEND = 2,
		REDIRECTION_HEREDOC = 3,
		REDIRECTION_INDEFINED = -1,
//		REDIRECTION_TEXT,
	} e_redirection;
	t_native_redirection	*next;
}	t_native_redirection;

typedef struct s_substring t_substring;
typedef struct s_substring
{
	char					*remaining_line;
	t_native_argument		*n_arguments;
	t_native_redirection	*n_redirections;
	t_substring				*next;
}	t_substring;


typedef struct s_command_line t_command_line;
typedef struct s_command_line
{
	bool				flag;
	t_substring			*substrings;
}	t_command_line;



size_t	ft_lst_size1(t_substring *head);
size_t	ft_lst_size2(t_native_redirection *head);
size_t	ft_lst_size3(t_native_argument *head);

t_substring	*ft_lst_last1(t_substring *head);
t_native_redirection	*ft_lst_last2(t_native_redirection *head);
t_native_argument	*ft_lst_last3(t_native_argument *head);

void	ft_lst_add_back1(t_substring **head, t_substring *new_element);
void	ft_lst_add_back2(t_native_redirection **head, t_native_redirection *new_element);
void	ft_lst_add_back3(t_native_argument **head, t_native_argument *new_element);

void	ft_lst_print(t_command_line *command_line, int fd);
void	print_e_redirection (int e_redirection, int fd);

void	free_all(t_command_line **command_line);
void	free_command_line(t_command_line **command_line);
void	free_substring(t_substring **substrings);
void	free_n_redirection(t_native_redirection **redirections);
void	free_n_argument(t_native_argument **arguments);

//void		ft_lst_delone(t_element **head, t_element *element_to_del);

#endif