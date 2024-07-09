/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:13 by drabarza          #+#    #+#             */
/*   Updated: 2024/07/08 19:55:36 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_export(t_exec_struct *exec_struct)
{
	(void)exec_struct;
	return ;
}

static t_envp_struct	*ft_lstnew(char *name, char *value)
{
	t_envp_struct	*lst;

	lst = malloc(sizeof(t_envp_struct));
	if (!lst)
		return (NULL);
	lst->name = ft_strdup(name);
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = NULL;
	return (lst);
}

static void	add_export(t_exec_struct *exec_struct, \
	char *argument)
{
	t_envp_struct	*env;	
	int				len_name;

	env = exec_struct->envp_struct;
	len_name = search_first_occurence(argument, '=');
		if (len_name == 0)
			len_name = (int)ft_strlen(argument);
	while (env)
	{
		if (!ft_strncmp(env->name, argument, len_name))
		{
			free(env->value);
			env->value = ft_substr(argument, len_name + 1, ft_strlen(argument));
			return ;
		}
		env = env->next;
	}
	env = exec_struct->envp_struct;
	if (len_name == 0)
	{
		ft_lst_add_back6(&exec_struct->envp_struct, ft_lstnew \
			(ft_substr(argument, 0, ft_strlen(argument)), NULL));
		return ;
	}
	ft_lst_add_back6(&exec_struct->envp_struct, \
	ft_lstnew(ft_substr(argument, 0, len_name), \
	ft_substr(argument, len_name + 1, ft_strlen(argument))));
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

	(void)print_export;
	arguments = exec_arguments->next;
	/*if (!arguments)
	{
	    print_export(exec_struct);
		return ;
	}*/
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
