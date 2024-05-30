#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "includes/libft_utils.h"
# include "includes/linked_list_utils.h"

# include <stdio.h>//to delete














void			print_arr(char **arr);
//!t_command_line 	*parse_command_line(char *str);
t_command_line 	*parse_command_line(char *str, int fd);
void	cut_remaining_line_on_pipes(t_command_line **command_line, char *remaining_line);
int		parse_substrings(char **remaining_line, t_command_line *command_line);
int		get_arguments_and_redirections(t_substring **substring, char **remaining_line);
int		get_redirections(char **remaining_line, t_substring *substring);
int		get_arguments(char **remaining_line, t_substring *substring);

int		init_native_argument_struct(t_native_argument **n_argument);
int		init_native_redirection_struct(t_native_redirection **n_redirection);
int		init_expanded_argument_struct(t_expanded_argument **exp_argument);
int		init_expanded_redirection_struct(t_expanded_redirection **exp_redirection);
int		init_substring_struct(t_substring **substring);
int		init_command_line_struct(t_command_line **command_line);

int		count_len_to_cut(char *remaining_line);
int		count_len_to_reach_first_quote_or_ifs(char *remaining_line);
int		count_len_to_next_quotes(char *remaining_line, char *c, int flag);
int		check_char_validity(char *remaining_line, int len_to_quote, int flag, int j);

unsigned int count_angled_bracket(char *str);

void	expand_contents(t_command_line **command_line);
//t_expanded_redirection *expand_redirections(t_substring *substring, t_native_redirection *n_redirection);
void	expand_redirections(t_substring *substring, t_native_redirection *n_redirection);
int		redirec(t_native_redirection **n_redirection, char **definitive_content);
//t_expanded_argument *expand_arguments(t_substring *substring, t_native_argument *n_argument);
void	expand_arguments(t_substring *substring, t_native_argument *n_argument);
size_t	get_len_and_extract_between_single_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_with_single_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_between_double_quotes(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_quote(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_dollar(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_quote_or_dollar(char *str, char **extracted_line);
size_t	get_len_and_extract_until_next_separator(char *str, char **extracted_line);

void	complete_expand_content(char **str);
size_t	simple_expand_content(char *str, char **extracted_line);
void	expand_string_between_single_quotes(char **str);
void	expand_string_after_dollar(char **str);
char	*expand_variables(char **remaining_line);
int     is_remaining_chars(char *str, char *list_of_char);




void	error_allocation(t_command_line **command_line);
void	error_handling(t_command_line **command_line);

#endif