/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:13 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/09 22:23:40 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* static int	is_range(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		k;
	
	str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_abcdefghijklmnopqrstvuwxyz";
	i = 0;
	j = 0;
	k = 0;
	while(s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			while(s1[i] != str[j])
				j++;
			while(s2[i] != str[k])
				k++;
			if (j > k)
				return (0);
			else
				return (1);
		}
		i++;
	}
	if (!s1[j])
				return (0);
			else
				return (1);
} */


static void	ft_lstdelone(t_envp_struct *element_to_del)
{
	if (!element_to_del)
		return ;
	element_to_del->name = free_and_null(element_to_del->name);
	element_to_del->value = free_and_null(element_to_del->value);
	free(element_to_del);
}

/*void add_node_back(t_envp_struct **head, t_envp_struct *node_to_add)
{
	t_envp_struct *temp;

    if (*head == NULL)
    {
        *head = node_to_add;
    }
    else
    {
        temp = *head;
        temp->next = node_to_add;
    }
}*/

static t_envp_struct	*ft_lstnew(char *name, char *value, bool equal)
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

t_envp_struct *copy_envp_struct(t_envp_struct *envp_struct)
{
	t_envp_struct	*copy;
	t_envp_struct	*new_element;
	t_envp_struct	*cursor;
//	size_t 			mnmemb;

//	nmemb = ft_lst_size6(envp_struct);
//	copy = ft_calloc(nmemb, sizeof(t_envp_struct));
//	if (!copy)
//		return (NULL);
	cursor = envp_struct;
	while (cursor)
	{
		new_element = ft_lstnew(cursor->name, cursor->value, cursor->equal);
		ft_lst_add_back6(&copy, new_element);
		cursor = cursor->next;
	}
	return (copy);
}

static void	print_export(t_envp_struct *envp_struct)
{
	t_envp_struct	*sorted_envp;
	t_envp_struct	*tmp_envp;
	t_envp_struct	*node_to_move;
	t_envp_struct	*previous_node;
	t_envp_struct	*node_to_free;
	int				i;
	int				hits;;

	sorted_envp = copy_envp_struct(envp_struct);
//	ft_envp_struct_lst_print(envp_struct, 1);
//	printf("\n");
	hits = 1;
	while (hits != 0)
	{
		hits = 0;;
		i = 0;
		tmp_envp = sorted_envp;
		previous_node = NULL;
		while (tmp_envp != NULL && tmp_envp->next != NULL )
		{
			if (ft_strcmp(tmp_envp->name, tmp_envp->next->name) > 0)
			{
				node_to_move = ft_lstnew(tmp_envp->next->name, tmp_envp->next->value, tmp_envp->next->equal);
				node_to_move->next = tmp_envp;
				node_to_free = tmp_envp->next;
				tmp_envp->next = tmp_envp->next->next;
				ft_lstdelone(node_to_free);
				if (i)
					previous_node->next = node_to_move;
				tmp_envp = node_to_move;
				hits++;
			}
			i++;
			if (i == 1)
				sorted_envp = tmp_envp;
			previous_node = tmp_envp;
			tmp_envp = tmp_envp->next;
		}
	}
	ft_envp_struct_lst_print(sorted_envp, 1);
	free_envp_struct(&sorted_envp);
	
}

static void	add_export(t_exec_struct *exec_struct, \
	char *argument)
{
	t_envp_struct	*env;	
	int				len_name;

	env = exec_struct->envp_struct;
	len_name = search_first_occurence(argument, '=');
	if (len_name == 0)
	{
		ft_lst_add_back6(&exec_struct->envp_struct, ft_lstnew \
			(ft_substr(argument, 0, ft_strlen(argument)), NULL, 0));
		return ;
	}
	while (env)
	{
		if (!ft_strncmp(env->name, argument, len_name))
		{
			free(env->value);
			env->value = ft_substr(argument, len_name + 1, ft_strlen(argument));
			env->equal = 1;
			return ;
		}
		env = env->next;
	}
	env = exec_struct->envp_struct;
	ft_lst_add_back6(&exec_struct->envp_struct, \
	ft_lstnew(ft_substr(argument, 0, len_name), \
	ft_substr(argument, len_name + 1, ft_strlen(argument)), 1));
}

static int	is_alpha(char *argument)
{
	int	i;

	i = 0;
	if ((argument[0] >= '0' && argument[0] <= '9') || argument[0] == '=')
		return (1);
	while (argument[i])
	{
		if (argument[i] == '=')
			return (0);
		if ((argument[i] < 'a' || argument[i] > 'z')
			&& (argument[i] < 'A' || argument[i] > 'Z'))
		{
			if ((argument[i] < '0' || argument[i] > '9') && argument[i] != '_')
				return (1);
		}
		i++;
	}
	return (0);
}

void	export(t_exec_struct *exec_struct, t_exec_argument *exec_arguments)
{
	t_exec_argument	*arguments;

	arguments = exec_arguments->next;
	if (!arguments)
	{
	    print_export(exec_struct->envp_struct);
		return ;
	}
	while (arguments)
	{
		if (!strcmp(arguments->argument, "_"))
		{
			return ;
		}
		if (is_alpha(arguments->argument))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(arguments->argument, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exec_struct->command_line->current_exit_code = 1;
			return ;
		}
		else
			add_export(exec_struct, arguments->argument);
		arguments = arguments->next;
	}
}
