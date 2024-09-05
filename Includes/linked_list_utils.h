/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 16:33:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/05 11:22:01 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

# include "libft_utils.h"

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

/*
* linked_list_init_1.c
*/

int					init_envp_struct(t_envp_struct **envp_struct);
int					init_command_line_struct(t_command_line **command_line);
int					init_substring_struct(t_substring **substring, \
					t_command_line **command_line);

/*
* linked_list_init_2.c
*/

int					init_native_argument_struct( \
					t_native_argument **n_argument, \
					t_command_line **command_line);
int					init_native_redirection_struct( \
					t_native_redirection **n_redirection, \
					t_command_line **command_line);
int					init_expanded_argument_struct( \
					t_expanded_argument **exp_argument, \
					t_command_line **command_line);
int					init_expanded_redirection_struct( \
					t_expanded_redirection **exp_redirection, \
					t_command_line **command_line);

/*
* linked_list_init_3.c
*/

int					init_exec_struct(t_exec_struct **exec_struct);
int					init_exec_substring_struct( \
					t_exec_substring **exec_substring, \
					t_exec_struct **exec_struct);
int					init_exec_redirection_struct( \
					t_exec_redirection **exec_redirection, \
					t_exec_struct **exec_struct);
int					init_exec_argument_struct( \
					t_exec_argument **exec_argument, \
					t_exec_struct **exec_struct);

/*
* free_command_line_1.c
*/

void				free_all_command_line(t_command_line **command_line);

/*
* free_command_line_2.c
*/

void				free_substring(t_substring **substrings);

/*
* free_envp_struct.c
*/

void				free_envp_struct(t_envp_struct **envp_struct);

/*
* free_exec_struct.c
*/

void				free_all_exec_struct(t_exec_struct **exec_struct);

#endif