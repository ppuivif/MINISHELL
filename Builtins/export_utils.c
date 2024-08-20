/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:33:32 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 12:42:38 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_lstdelone(t_envp_struct *element_to_del)
{
	if (!element_to_del)
		return ;
	element_to_del->name = free_and_null(element_to_del->name);
	element_to_del->value = free_and_null(element_to_del->value);
	free(element_to_del);
}

t_envp_struct	*ft_lstnew(char *name, char *value, bool equal)
{
	t_envp_struct	*lst;

	lst = malloc(sizeof(t_envp_struct));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup(name);
	lst->equal = equal;
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = NULL;
	lst->next = NULL;
	return (lst);
}

static int	sort_envp(t_envp_struct **tmp_envp, \
t_envp_struct **previous_node, int *i)
{
	t_envp_struct	*node_to_move;
	t_envp_struct	*node_to_free;

	if (ft_strcmp((*tmp_envp)->name, (*tmp_envp)->next->name) > 0)
	{
		node_to_move = ft_lstnew((*tmp_envp)->next->name, \
		(*tmp_envp)->next->value, (*tmp_envp)->next->equal);
		node_to_move->next = *tmp_envp;
		node_to_free = (*tmp_envp)->next;
		(*tmp_envp)->next = (*tmp_envp)->next->next;
		ft_lstdelone(node_to_free);
		if (*i)
			(*previous_node)->next = node_to_move;
		*tmp_envp = node_to_move;
		(*i)++;
		return (1);
	}
	(*i)++;
	return (0);
}

static void	ft_lst_print(t_envp_struct *envp_struct, int fd)
{
	size_t			i;
	t_envp_struct	*tmp;

	i = 0;
	tmp = envp_struct;
	while (tmp && i < ft_lst_size6(envp_struct))
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->name, fd);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
		i++;
	}
}

t_envp_struct	*copy_envp_struct(t_envp_struct *envp_struct)
{
	t_envp_struct	*copy;
	t_envp_struct	*new_element;
	t_envp_struct	*cursor;

	copy = NULL;
	new_element = NULL;
	cursor = envp_struct;
	while (cursor)
	{
		new_element = ft_lstnew(cursor->name, cursor->value, cursor->equal);
		ft_lst_add_back6(&copy, new_element);
		cursor = cursor->next;
	}
	return (copy);
}

void	print_export(t_envp_struct *envp_struct)
{
	t_envp_struct	*sorted_envp;
	t_envp_struct	*tmp_envp;
	t_envp_struct	*previous_node;
	int				i;
	int				hits;

	sorted_envp = copy_envp_struct(envp_struct);
	hits = 1;
	while (hits != 0)
	{
		hits = 0;
		i = 0;
		tmp_envp = sorted_envp;
		previous_node = NULL;
		while (tmp_envp != NULL && tmp_envp->next != NULL )
		{
			hits += sort_envp(&tmp_envp, &previous_node, &i);
			if (i == 1)
				sorted_envp = tmp_envp;
			previous_node = tmp_envp;
			tmp_envp = tmp_envp->next;
		}
	}
	ft_lst_print(sorted_envp, 1);
	free_envp_struct(&sorted_envp);
}
