#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft_utils.h"

# include <stdio.h>//to delete


typedef struct s_envp_struct t_envp_struct;
typedef struct s_envp_struct
{
	char			*content;
	t_envp_struct	*next;
}t_envp_struct;

typedef enum e_redirection
{
	REDIRECTION_OUTFILE = 0,
	REDIRECTION_INFILE = 1,
	REDIRECTION_INDEFINED = 2,
	REDIRECTION_APPEND = 3,
	REDIRECTION_HEREDOC = 4,
	REDIRECTION_AMBIGUOUS = 5,
} e_redirection;

typedef struct s_expanded_argument t_expanded_argument;
typedef struct s_expanded_argument
{
	bool				alloc_succeed;
	char				*content;
	t_expanded_argument	*next;
}	t_expanded_argument;

typedef struct s_expanded_redirection t_expanded_redirection;
typedef struct s_expanded_redirection
{
	bool					alloc_succeed;
	char					*content;
	e_redirection			e_redirection;
	t_expanded_redirection	*next;
}	t_expanded_redirection;

typedef struct s_native_argument t_native_argument;
typedef struct s_native_argument
{
	char				*content;
	t_native_argument	*next;
}	t_native_argument;

typedef struct s_native_redirection t_native_redirection;
typedef struct s_native_redirection
{
	//bool					alloc_succeed;
	char					*content;
	e_redirection			e_redirection;
/*	enum
	{
		REDIRECTION_OUTFILE = 0,
		REDIRECTION_INFILE = 1,
		REDIRECTION_INDEFINED = 2,
		REDIRECTION_APPEND = 3,
		REDIRECTION_HEREDOC = 4,
//		REDIRECTION_TEXT = 5,
	} e_redirection;*/
	t_native_redirection	*next;
}	t_native_redirection;

typedef struct s_substring t_substring;
typedef struct s_substring
{
	char					*remaining_line;
	t_native_argument		*n_arguments;
	t_native_redirection	*n_redirections;
	t_expanded_argument		*exp_arguments;
	t_expanded_redirection	*exp_redirections;
	t_substring				*next;
}	t_substring;


typedef struct s_command_line t_command_line;
typedef struct s_command_line
{
	char			**argv;
	int				previous_exit_code;
	int				current_exit_code;
	t_substring		*substrings;
	t_envp_struct	*envp_struct;
}	t_command_line;


typedef struct s_exec_redirection t_exec_redirection;
typedef struct s_exec_redirection
{
	int					substring_index;
	char				*file;
	e_redirection		e_redirection;
	int					fd_input;
	int					fd_output;
	t_exec_redirection	*next;
}t_exec_redirection;

typedef struct s_exec_argument t_exec_argument;
typedef struct s_exec_argument
{
	char	*argument;
	t_exec_argument	*next;
}t_exec_argument;

typedef struct s_exec_substring t_exec_substring;
typedef struct s_exec_substring
{
	int					index;
	t_exec_redirection	*exec_redirections;
	t_exec_argument		*exec_arguments;
	char				**cmd_arr;
	char				*path_with_cmd;
	t_exec_substring			*next;
}t_exec_substring;

typedef struct s_exec_struct
{
	int				exit_code;
	t_exec_substring	*exec_substrings;
	t_envp_struct	*envp_struct;
	t_command_line	*command_line;
}t_exec_struct;


void	ft_envp_struct_lst_print(t_envp_struct *envp_struct, int fd);
void	ft_native_lst_print(t_command_line *command_line, int fd);
void	ft_expanded_lst_print(t_command_line *command_line, int fd);
void	ft_execution_lst_print(t_exec_struct *exec_struct, int fd);
void	print_e_redirection (int e_redirection, int fd);


size_t	ft_lst_size1(t_substring *head);
size_t	ft_lst_size2(t_native_redirection *head);
size_t	ft_lst_size3(t_native_argument *head);
size_t	ft_lst_size4(t_expanded_redirection *head);
size_t	ft_lst_size5(t_expanded_argument *head);
size_t	ft_lst_size6(t_envp_struct *head);
size_t	ft_lst_size7(t_exec_substring *head);
size_t	ft_lst_size8(t_exec_redirection *head);
size_t	ft_lst_size9(t_exec_argument *head);

t_substring				*ft_lst_last1(t_substring *head);
t_native_redirection	*ft_lst_last2(t_native_redirection *head);
t_native_argument		*ft_lst_last3(t_native_argument *head);
t_expanded_redirection	*ft_lst_last4(t_expanded_redirection *head);
t_expanded_argument		*ft_lst_last5(t_expanded_argument *head);
t_envp_struct			*ft_lst_last6(t_envp_struct *head);
t_exec_substring		*ft_lst_last7(t_exec_substring *head);
t_exec_redirection		*ft_lst_last8(t_exec_redirection *head);
t_exec_argument			*ft_lst_last9(t_exec_argument *head);

void	ft_lst_add_back1(t_substring **head, t_substring *new_element);
void	ft_lst_add_back2(t_native_redirection **head, t_native_redirection *new_element);
void	ft_lst_add_back3(t_native_argument **head, t_native_argument *new_element);
void	ft_lst_add_back4(t_expanded_redirection **head, t_expanded_redirection *new_element);
void	ft_lst_add_back5(t_expanded_argument **head, t_expanded_argument *new_element);
void	ft_lst_add_back6(t_envp_struct **head, t_envp_struct *new_element);
void	ft_lst_add_back7(t_exec_substring **head, t_exec_substring *new_element);
void	ft_lst_add_back8(t_exec_redirection **head, t_exec_redirection *new_element);
void	ft_lst_add_back9(t_exec_argument **head, t_exec_argument *new_element);

void	free_envp_struct(t_envp_struct **envp_struct);
void	free_all_command_line(t_command_line **command_line);
void	free_all_exec_struct(t_exec_struct **exec_struct);
void	free_substring(t_substring **substrings);

//void		ft_lst_delone(t_element **head, t_element *element_to_del);

#endif