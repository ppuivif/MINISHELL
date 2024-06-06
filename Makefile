CC = gcc
FLAGS = -Wall -Werror -Wextra -g -Iincludes
NAME  = minishell
#SRCDIR = src
#OBJDIR = obj
SRCS = minishell.c \
		get_and_free_envp.c arr_utils.c\
		parsing_substrings.c parsing_redirections.c parsing_arguments.c\
		parsing_utils_1.c parsing_utils_2.c\
		expand_contents.c expand_redirections.c expand_arguments.c\
		expand_utils_1.c expand_utils_2.c expand_utils_3.c expand_utils_4.c expand_utils_5.c\
		build_execution.c check_exec_redirections.c check_exec_arguments.c error_handling.c

#SRCS += libft/libft_utils_1.c libft/libft_utils_2.c libft/libft_utils_3.c libft/libft_utils_4.c\
#		linked_list/linked_list_utils_1.c linked_list/linked_list_utils_2.c linked_list/init.c

SRCS += libft_utils_1.c libft_utils_2.c libft_utils_3.c libft_utils_4.c libft_utils_5.c libft_utils_6.c\
		linked_list_utils_1.c linked_list_utils_2.c init.c free_command_line_1.c free_command_line_2.c\
		free_exec_struct.c\
		GNL/get_next_line_utils.c GNL/get_next_line.c

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