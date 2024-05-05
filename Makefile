CC = gcc
FLAGS = -Wall -Werror -Wextra -g
NAME  = minishell
#SRCDIR = src
#OBJDIR = obj
SRCS = minishell.c \
		arr_utils.c parsing_1.c init.c

SRCS += libft_utils_1.c libft_utils_2.c libft_utils_3.c libft_utils_4.c\
		linked_list_utils_1.c linked_list_utils_2.c

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