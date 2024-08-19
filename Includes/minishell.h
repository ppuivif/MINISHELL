/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:11:42 by ppuivif           #+#    #+#             */
/*   Updated: 2024/08/19 17:13:31 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft_utils.h"
# include "linked_list_utils.h"
# include "../GNL/get_next_line.h"//to delete

# include <stdio.h>//to delete
# include <fcntl.h>
# include <sys/wait.h>
#include <dirent.h>//for opendir in check_exec_arguments.c
#include <sys/stat.h>//for stat
#include <sys/ioctl.h>

#include <errno.h>//to delete
#include <signal.h>
# include <limits.h>

# ifndef GLOBAL
# define GLOBAL
extern int	g_sign;
# endif



void			print_arr(char **arr);


void			get_envp(char **envp, t_envp_struct **envp_struct, char *line);

t_command_line 	*parse_command_line(char **argv, char *str, t_envp_struct **envp_struct, int exit_code);
int				get_redirections(char **remaining_line, t_substring *substring, t_command_line **command_line);
int				get_arguments(char **remaining_line, t_substring *substring, t_command_line **command_line);


int				is_pipe_latest_character(char **remaining_line);
int				is_pipe_first_character(char *remaining_line);
int				count_len_to_cut(char *remaining_line);
unsigned int	count_angled_bracket(char *str);



int		init_envp_struct(t_envp_struct **envp_struct);
int		init_native_argument_struct(t_native_argument **n_argument);
int		init_nativt_redirection_struct(t_nativt_redirection **n_redirection);
int		init_expanded_argument_struct(t_expanded_argument **exp_argument);
int		init_expanded_redirection_struct(t_expanded_redirection **exp_redirection);
int		init_substring_struct(t_substring **substring);
int		init_command_line_struct(t_command_line **command_line);
int		init_exec_struct(t_exec_struct **exec_struct);
int		init_exec_substring_struct(t_exec_substring **exec_substring);
int		init_exec_redirection_struct(t_exec_redirection **exec_redirection);
int		init_exec_argument_struct(t_exec_argument **exec_argument);


void	expand_contents(t_command_line **command_line);
void	expand_redirections(t_substring *substring, t_nativt_redirection *n_redirection, t_command_line **command_line);
int		expand_arguments(t_substring *substring, t_native_argument *n_argument, t_command_line **command_line);
void	add_exp_arguments(t_expanded_argument **exp_arguments, char **definitive_content);

size_t	get_len_and_extract_between_single_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_with_single_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_between_double_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_quote(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_dollar(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_dollar_first_dollar_excluded\
		(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_quote_or_dollar(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_separator(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_separator_first_dollar_included\
		(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_separator_dollar_excluded(char *str, char **extracted_line);
size_t	get_len_and_extract_after_first_dollar(char *str, char **extracted_line);
size_t	handle_special_characters_after_dollar(char *str, char **extracted_line, \
t_command_line **command_line, bool flag_keep_dollar);

void	expand_string_after_dollar1(char **str, t_envp_struct *envp_struct, t_command_line **command_line);
void	expand_string_after_dollar2(char *str, t_expanded_argument **exp_arguments,t_envp_struct *envp_struct, char **definitive_content);
void	complete_expand_content_of_redirections(char **str, t_command_line **command_line);
void	complete_expand_content_of_arguments(char **extracted_line, t_command_line **command_line, bool flag_keep_dollar);
size_t	simple_expand_content_of_redirections(char *str, char **extracted_line, t_command_line **command_line);
size_t	simple_expand_content_of_arguments(char *str, t_expanded_argument **exp_arguments, char **definitive_content, t_command_line **command_line);
void	expand_content_when_heredoc(char **str, t_envp_struct *envp_struct, t_command_line **command_line, bool flag_for_expand);
int		add_to_definitive_content(char **definitive_content, char *extracted_line);



void	build_exec_struct(t_exec_struct **exec_struct);

int		open_and_check_file(t_expanded_redirection *exp_redirections , t_exec_redirection **exec_redirection, t_exec_substring **exec_substring, t_exec_struct *exec_struct);

void	check_exec_arguments(t_exec_substring **exec_substring, t_exec_struct **exec_struct);
char	**build_envp_arr(t_exec_struct **exec_struct);
//char	**search_path(char **envp);
char	**search_path(t_envp_struct *envp_struct);
void	build_cmd_arr(t_exec_substring **exec_substring, t_exec_struct **exec_struct);
void	check_command_with_options(t_exec_substring **exec_substring, t_exec_struct **exec_struct);
void	check_path_in_envp(t_exec_substring **exec_substring, t_exec_struct **exec_struct);
int		check_path_cmd_validity(char **path, t_exec_substring **exec_substring);

void	execution(t_exec_struct **exec_struct);
//void	exec_child(t_exec_substring *substrings, int fd_in, int fd_out, char **envp, t_exec_struct **exec_struct);
void	exec_child(t_exec_substring *substring, int fd_in, int fd_out, char **envp_arr, t_exec_struct **exec_struct, int *pid_arr, int *fd, int i);


/*
* error_handling.c
*/

void	error_allocation_exec_struct_and_exit(t_exec_struct **exec_struct);
void	error_allocation_command_line_and_exit(t_command_line **command_line);
void	error_pipe_creation_and_exit(t_exec_struct **exec_struct);
void	error_fork_creation_and_exit(t_exec_struct **exec_struct);

//Builtin
void	exec_builtin(t_exec_struct *exec_struct, t_exec_substring *substring, char **envp_arr);
void	echo(t_exec_argument *exec_arguments);
void	pwd(void);
void	exit_builting(t_exec_struct *exec_struct, t_exec_argument *exec_arguments, char **envp_arr);
int		check_is_builtin(t_exec_argument *exec_arguments);
void	cd(t_exec_struct *exec_struct, t_exec_argument *exec_arguments);
void	env(t_exec_struct *exec_struct);
void	unset(t_exec_struct *exec_struct, t_exec_argument *exec_arguments);
void	export(t_exec_struct *exec_struct, t_exec_argument *exec_arguments);
int		ft_aatoi(char *nptr, t_exec_struct *exec_struct, char **envp_arr);
void	message_error(char *str, t_exec_struct *exec_struct, char **envp_arr);

//Signals
void signals(int sign);

#endif
