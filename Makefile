CC = gcc
FLAGS = -Wall -Werror -Wextra -g -IIncludes -ILinked_list_utils -ILibft_utils -IParsing_utils -IExpand_utils -IExec_utils
NAME  = minishell
#SRCDIR = src
#OBJDIR = obj

#SRCS = minishell_for_tests.c \
#SRCS = minishell_for_execution.c \

SRCS = minishell_for_execution.c \
		get_envp.c\
		parsing_substrings.c\
		parsing_redirections.c\
		parsing_arguments.c\
		expand_contents.c\
		expand_redirections.c\
		expand_arguments.c\
		build_execution.c\
		check_exec_redirections.c\
		check_exec_arguments.c\
		error_handling.c\
		execution_parent.c\
		execution_child.c\
		signals.c\
		
SRCS += Builtins/echo.c\
		Builtins/pwd.c\
		Builtins/exit.c\
		Builtins/exit_utils.c\
		Builtins/cd.c\
		Builtins/env.c\
		Builtins/unset.c\
		Builtins/export.c\
		Builtins/add_export.c\
		Builtins/export_utils.c\
		Builtins/builtin_utils.c\

SRCS += Libft_utils/libft_utils_1.c\
		Libft_utils/libft_utils_2.c\
		Libft_utils/libft_utils_3.c\
		Libft_utils/libft_utils_4.c\
		Libft_utils/libft_utils_5.c\
		Libft_utils/libft_utils_6.c\

SRCS += Linked_list_utils/linked_list_init_1.c\
		Linked_list_utils/linked_list_init_2.c\
		Linked_list_utils/linked_list_init_3.c\
		Linked_list_utils/linked_list_utils_1.c\
		Linked_list_utils/linked_list_utils_2.c\
		Linked_list_utils/linked_list_utils_3.c\
		Linked_list_utils/linked_list_utils_4.c\
		Linked_list_utils/linked_list_utils_5.c\
		Linked_list_utils/linked_list_utils_6.c\
		Linked_list_utils/linked_list_utils_7.c\
		Linked_list_utils/linked_list_utils_8.c\
		Linked_list_utils/linked_list_utils_9.c\

SRCS += Parsing_utils/parsing_utils.c\

SRCS += Expand_utils/expand_utils_1.c\
		Expand_utils/expand_utils_2.c\
		Expand_utils/expand_utils_3.c\
		Expand_utils/expand_utils_4.c\
		Expand_utils/expand_utils_5.c\
		Expand_utils/expand_utils_6.c\
		Expand_utils/expand_utils_7.c\
		Expand_utils/expand_utils_8.c\
		Expand_utils/expand_utils_9.c\
		Expand_utils/expand_utils_10.c\
		Expand_utils/expand_utils_11.c\
		Expand_utils/expand_utils_12.c\
		Expand_utils/expand_utils_13.c\
		Expand_utils/expand_utils_14.c\
		Expand_utils/expand_utils_15.c\
		Expand_utils/expand_utils_16.c\
		Expand_utils/expand_utils_17.c\

SRCS += Exec_utils/exec_utils_1.c\
		Exec_utils/exec_utils_2.c\
		Exec_utils/exec_utils_3.c\


SRCS +=	Free_utils/free_command_line_1.c\
		Free_utils/free_command_line_2.c\
		Free_utils/free_envp_struct.c \
		Free_utils/free_exec_struct.c\


SRCS += linked_list_utils_for_print.c\
		GNL/get_next_line_utils.c\
		GNL/get_next_line.c\
#GNL to delete

OBJECTS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
		$(CC) $(FLAGS) $(OBJECTS) -o $@ -lreadline
		@clear

#$(OBJDIR):
#	mkdir -p $(OBJDIR)

%.o : %.c
		$(CC) $(FLAGS) -c $< -o $@

clean :
		rm -rf $(OBJECTS)

fclean : clean
		rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
