#ifndef LINKED_LIST_UTILS_H
# define LINKED_LIST_UTILS_H

# include <stdlib.h>
# include <stdbool.h>

# include "libft_utils.h"

typedef struct s_element t_element;
typedef struct s_element
{
	bool		did_succeed;
	char		*line;
	char		**arr;
	char		*path;
	t_element	*next;
}	t_element;

/*typedef struct s_list
{
	int			size;
	t_element	*head;
}	t_list;*/

//int			init_list_struct(t_list	**stack, int size);
//void		init_element_struct(t_element *element);
//t_element	*ft_lst_dc_new(char *line, char **arr, char *path);
void		ft_lst_add_back(t_element **head, t_element *new_element);
void		ft_lst_add_front(t_element **head, t_element *new_element);
t_element	*ft_lst_last(t_element *head);
size_t		ft_lst_size(t_element *head);
void		ft_lst_delone(t_element **head, t_element *element_to_del);
void		ft_lst_print(t_element *head);

#endif