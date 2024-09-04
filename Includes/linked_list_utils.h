/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:33:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/02 17:12:24 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft_utils.h"

# include <stdio.h>//to delete

typedef struct s_envp_struct	t_envp_struct;
typedef struct s_envp_struct
{
	char			*name;
	bool			equal;
	char			*value;
	t_envp_struct	*next;
}	t_envp_struct;

typedef enum t_redirection_type
{
	REDIRECTION_OUTFILE = 0,
	REDIRECTION_INFILE = 1,
	REDIRECTION_INDEFINED = 2,
	REDIRECTION_APPEND = 3,
	REDIRECTION_HEREDOC = 4,
	REDIRECTION_AMBIGUOUS = 5,
}	t_redirection;

typedef enum t_builtin_type
{
	ISNOT_BUILTIN = 0,
	IOPUT_ACCEPTED = 1,
	IOPUT_NOT_ACCEPTED = 2,
}	t_builtin;

typedef struct s_expanded_argument
{
	char						*content;
	struct s_expanded_argument	*next;
}	t_expanded_argument;

typedef struct s_expanded_redirection
{
	int								exp_redirection_index;
	char							*content;
	t_redirection					t_redirection;
	bool							flag_for_expand;
	struct s_expanded_redirection	*next;
}	t_expanded_redirection;

typedef struct s_native_argument
{
	char						*content;
	struct s_native_argument	*next;
}	t_native_argument;

typedef struct s_native_redirection
{
	char						*content;
	t_redirection				t_redirection;
	bool						flag_for_expand;
	struct s_native_redirection	*next;
}	t_native_redirection;

typedef struct s_substring
{
	int						substring_index;
	char					*remaining_line;
	t_native_argument		*n_arguments;
	t_native_redirection	*n_redirections;
	t_expanded_argument		*exp_arguments;
	t_expanded_redirection	*exp_redirections;
	struct s_substring		*next;
}	t_substring;

typedef struct s_command_line
{
	char			**argv;
	int				previous_exit_code;
	int				current_exit_code;
	t_substring		*substrings;
	t_envp_struct	*envp_struct;
}	t_command_line;

typedef struct s_exec_redirection
{
	char						*file;
	t_redirection				t_redirection;
	int							fd_input;
	int							fd_output;
	struct s_exec_redirection	*next;
}	t_exec_redirection;

typedef struct s_exec_argument
{
	char					*argument;
	bool					is_argument_valid;
	t_builtin				is_builtin;
	struct s_exec_argument	*next;
}	t_exec_argument;

typedef struct s_exec_substring
{
	t_exec_redirection		*exec_redirections;
	bool					is_previous_file_opened;
	t_exec_argument			*exec_arguments;
	char					**cmd_arr;
	char					*path_with_cmd;
	int						*pid_arr;
	int						fd_in;
	int						fd_out;
	int						fd[2];
	struct s_exec_substring	*next;
}	t_exec_substring;

typedef struct s_exec_struct
{
	int					exit_code;
	t_exec_substring	*exec_substrings;
	t_envp_struct		*envp_struct;
	t_command_line		*command_line;
}	t_exec_struct;

/*
* linked_list_utils_for_print to delete
*/

void				ft_envp_struct_lst_print(t_envp_struct *envp_struct, \
					int fd);
void				ft_native_lst_print(t_command_line *command_line, int fd);
void				ft_expanded_lst_print(t_command_line *command_line, int fd);
void				ft_execution_lst_print(t_exec_struct *exec_struct, int fd);
void				print_t_redirection(int t_redirection, int fd);

/*
* linked_list_utils1.c for substring
*/

size_t				ft_lst_size1(t_substring *head);
void				ft_lst_add_back1(t_substring **head, \
					t_substring *new_element);

/*
* linked_list_utils2.c for native edirection
*/

size_t				ft_lst_size2(t_native_redirection *head);
void				ft_lst_add_back2(t_native_redirection **head, \
					t_native_redirection *new_element);

/*
* linked_list_utils3.c for native argument
*/

size_t				ft_lst_size3(t_native_argument *head);
void				ft_lst_add_back3(t_native_argument **head, \
					t_native_argument *new_element);

/*
* linked_list_utils4.c for expanded redirection
*/

size_t				ft_lst_size4(t_expanded_redirection *head);
void				ft_lst_add_back4(t_expanded_redirection **head, \
					t_expanded_redirection *new_element);

/*
* linked_list_utils5.c for expanded argument
*/

size_t				ft_lst_size5(t_expanded_argument *head);
void				ft_lst_add_back5(t_expanded_argument **head, \
					t_expanded_argument *new_element);

/*
* linked_list_utils6.c for envp
*/

size_t				ft_lst_size6(t_envp_struct *head);
void				ft_lst_add_back6(t_envp_struct **head, \
					t_envp_struct *new_element);

/*
* linked_list_utils7.c for exec substring
*/

t_exec_substring	*ft_lst_last7(t_exec_substring *head);
size_t				ft_lst_size7(t_exec_substring *head);
void				ft_lst_add_back7(t_exec_substring **head, \
					t_exec_substring *new_element);

/*
* linked_list_utils8.c for exec redirection
*/

size_t				ft_lst_size8(t_exec_redirection *head);
void				ft_lst_add_back8(t_exec_redirection **head, \
					t_exec_redirection *new_element);

/*
* linked_list_utils9.c for exec argument
*/

size_t				ft_lst_size9(t_exec_argument *head);
void				ft_lst_add_back9(t_exec_argument **head, \
					t_exec_argument *new_element);

#endif