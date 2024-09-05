/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 17:11:42 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/05 11:11:51 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "libft_utils.h"
# include "linked_list_utils.h"

# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# include <errno.h>
# include <signal.h>
# include <limits.h>

# ifndef GLOBAL
#  define GLOBAL

extern int	g_sign;
# endif

/*
* get_envp.c
*/

void			get_envp(char **envp, t_envp_struct **envp_struct);

/*
* parsing_substrings.c
*/

t_command_line	*parse_command_line(char **argv, char *str, \
				t_envp_struct **envp_struct, int exit_code);

/*
* parsing_redirections.c
*/

int				get_redirections(char **remaining_line, t_substring *substring, \
				t_command_line **command_line);

/*
* parsing_arguments.c
*/

int				get_arguments(char **remaining_line, t_substring *substring, \
				t_command_line **command_line);

/*
* parsing_utils.c
*/

int				is_pipe_latest_character(char **remaining_line);
int				is_pipe_first_character(char *remaining_line);
int				count_len_to_cut(char *remaining_line);
unsigned int	count_angled_bracket(char *str);

/*
* expand_contents.c
*/

void			expand_contents(t_command_line **command_line);

/*
* expand_redirections.c
*/

void			expand_redirections(t_substring *substring, \
				t_native_redirection *n_redirection, \
				t_command_line **command_line, \
				int exp_redirection_index);

/*
* expand_arguments.c
*/

void			expand_arguments(t_substring *substring, \
				t_native_argument *n_argument, t_command_line **command_line);

/*
* expand_utils_1.c
*/

int				get_len_and_extract_between_quotes(char *str, \
				char **extracted_line, t_command_line **command_line, char c);
int				get_len_and_extract_with_single_quotes(char *str, \
				char **extracted_line, t_command_line **command_line);
int				get_len_and_extract_until_next_quote(char *str, \
				char **extracted_line, t_command_line **command_line);
int				get_len_and_extract_until_next_dollar(char *str, \
				char **extracted_line, t_command_line **command_line);
int				get_len_and_extract_until_next_dollar_first_excluded( \
				char *str, char **extracted_line, \
				t_command_line **command_line);
/*
* expand_utils_2.c
*/

int				get_len_and_extract_until_next_quote_or_dollar(char *str, \
				char **extracted_line, t_command_line **command_line);
int				get_len_and_extract_until_next_separator(char *str, \
				char **extracted_line, t_command_line **command_line);
int				get_len_and_extract_until_next_separator_st_dollar_included( \
				char *str, char **extracted_line, \
				t_command_line **command_line);
int				get_len_and_extract_until_next_separator_dollar_excluded( \
				char *str, char **extracted_line, \
				t_command_line **command_line);
int				get_len_and_extract_after_first_dollar(char *str, \
				char **extracted_line, t_command_line **command_line);

/*
* expand_utils_3.c
*/

char			*expand_variables(char **remaining_line, \
				t_command_line **command_line);

/*
* expand_utils_4.c
*/

void			extract_argument_until_next_whitespace_or_dollar(char **str, \
				char **extracted_argument, t_command_line **command_line);
void			cut_variable_on_whitespaces( \
				t_expanded_argument **exp_arguments, char **variable, \
				bool *last_arg_with_wspaces, t_command_line **command_line);

/*
* expand_utils_5.c
*/

void			expand_string_after_dollar1(char **str, \
				t_command_line **command_line);
void			expand_string_after_dollar2(char *str, \
				t_expanded_argument **exp_arguments, \
				char **definitive_content, t_command_line **command_line);

/*
* expand_utils_6.c
*/

int				expand_content_when_dollar_not_first(char *str, \
				char **tmp, t_command_line **command_line);
void			complete_expand_content_of_redirections(char **str, \
				t_command_line **command_line);

/*
* expand_utils_7.c
*/

void			complete_expand_content_of_arguments(char **extracted_line, \
				t_command_line **command_line, bool flag_keep_dollar);

/*
* expand_utils_8.c
*/

int				is_non_valid_characters(char *str);
int				handle_quotes(char **extracted_line, \
				t_command_line **command_line, bool flag_keep_dollar);
int				handle_non_valid_characters(char *str, char **extracted_line, \
				t_command_line **command_line);
int				handle_double_dollar(char **extracted_line, \
				t_command_line **command_line);
int				handle_question_mark(char **extracted_line, \
				t_command_line **command_line);

/*
* expand_utils_9.c
*/

int				handle_equals_sign(char **extracted_line, \
				t_command_line **command_line);
int				handle_digits(char *str, char **extracted_line, \
				t_command_line **command_line);
int				handle_special_characters_after_dollar(char *str, \
				char **extracted_line, t_command_line **command_line, \
				bool flag_keep_dollar);
int				simple_expand_content_of_redirections(char *str, \
				char **extracted_line, t_command_line **command_line);

/*
* expand_utils_10.c
*/

void			add_to_definitive_content(char **definitive_content, \
				char *extracted_line, t_command_line **command_line, \
				char *str);
void			check_ambiguous_redirection(char **extracted_line, \
				t_native_redirection **n_redirection);
void			add_exp_arguments(t_expanded_argument **exp_arguments, \
				char **definitive_content, t_command_line **command_line);

/*
* expand_utils_11.c
*/

void			expand_content_when_heredoc(char **str, \
				t_command_line **command_line, bool flag_for_expand);

/*
* expand_utils_12.c
*/

int				open_heredoc_and_modify_exp_redirec(t_substring *substring, \
				t_expanded_redirection **exp_redirection, \
				t_exec_struct **exec_struct);

/*
* expand_utils_13.c
*/

int				assignment_ambiguous_redirection( \
				t_expanded_redirection *exp_redirection, \
				t_exec_redirection **exec_redirection);
int				check_outfile(t_expanded_redirection *exp_redirection, \
				t_exec_redirection **exec_redirection);
int				check_infile(t_expanded_redirection *exp_redirection, \
				t_exec_redirection **exec_redirection);

/*
* expand_utils_14.c
*/

int				check_dir_and_file_permission(char **cmd_arr, \
				t_exec_substring **exec_substring, \
				t_exec_struct **exec_struct);

/*
* expand_utils_15.c
*/

void			check_path_in_envp(t_exec_substring **exec_substring, \
				t_exec_struct **exec_struct);

/*
* expand_utils_16.c
*/

void			check_when_no_path(t_exec_substring **exec_substring, \
				t_exec_struct **exec_struct, char **path_envp);

/*
* expand_utils_17.c
*/

void			check_when_path_exists(t_exec_substring **exec_substring, \
				t_exec_struct **exec_struct, char **path_envp);

/*
* build_execution.c
*/

void			build_exec_struct(t_exec_struct **exec_struct);

/*
* check_exec_redirections.c
*/

int				open_and_check_file(t_expanded_redirection *exp_redirections, \
				t_exec_redirection **exec_redirection, \
				t_exec_substring **exec_substring);

/*
* check_exec_arguments.c
*/

void			check_exec_arguments(t_exec_substring **exec_substring, \
				t_exec_struct **exec_struct);

/*
* execution_parent.c
*/

void			execution(t_exec_struct **exec_struct);

/*
* execution_child.c
*/

void			exec_child(t_exec_substring *substring, char **envp_arr, \
				t_exec_struct **exec_struct);

/*
* exec_utils_1.c
*/

void			search_heredoc_and_modify_exp_redirec(t_substring *substring, \
				t_exec_struct **exec_struct);

/*
* exec_utils_2.c
*/

void			substrings_execution(t_exec_struct **exec_struct);

/*
* exec_utils_3.c
*/

char			**build_envp_arr(t_exec_struct **exec_struct);
int				search_last_input(t_exec_redirection *redirection, int fd_in);
int				search_last_output(t_exec_redirection *redirection, int fd_out);
void			fd_handle_in_parent(t_exec_substring **exec_substring);
int				get_exit_code_last_process(int *pid_arr, int i);

/*
* error_handling.c
*/

void			error_allocation_envp_struct_and_exit( \
				t_envp_struct **envp_struct);
void			error_allocation_exec_struct_and_exit( \
				t_exec_struct **exec_struct);
void			error_allocation_command_line_and_exit( \
				t_command_line **command_line);
void			error_pipe_creation_and_exit(t_exec_struct **exec_struct);
void			error_fork_creation_and_exit(t_exec_struct **exec_struct);

/*
* add.export.c
*/

int				search_var(t_envp_struct *envp_struct, char *str);
void			add_export(t_exec_struct *exec_struct, char *argument);
void			add2_export(t_exec_struct *exec_struct, char *argument);

/*
* builtin_utils.c
*/

int				error_option(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments, char *str);
void			exec_builtin(t_exec_struct *exec_struct, \
				t_exec_substring *substring, char **envp_arr);
int				check_is_builtin(t_exec_argument *exec_arguments);

/*
* cd.c
*/

void			cd(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments);

/*
* echo.c
*/

void			echo(t_exec_argument *exec_arguments);

/*
* env.c
*/

void			env(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments);

/*
* exit_utils.c
*/

int				ft_aatoi(char *nptr, t_exec_struct *exec_struct, \
				char **envp_arr);

/*
* exit.c
*/

void			message_error(char *str, t_exec_struct *exec_struct, \
				char **envp_arr);
void			exit_builting(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments, char **envp_arr);

/*
* export_utils.c
*/

void			print_export(t_envp_struct *envp_struct);

/*
* export.c
*/

t_envp_struct	*ft_lstnew(char *name, char *value, bool equal);
void			export(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments);

/*
* pwd.c
*/

void			pwd(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments);

/*
* unset.c
*/

void			unset(t_exec_struct *exec_struct, \
				t_exec_argument *exec_arguments);

/*
* signals
* .c
*/

void			signals(int sign);

#endif
