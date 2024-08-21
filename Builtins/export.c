/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:13 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/21 17:13:23 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static int	is_alpha(char *argument)
{
	int	i;

	i = 0;
	if ((argument[0] >= '0' && argument[0] <= '9') || argument[0] == '=')
		return (1);
	while (argument[i])
	{
		if (argument[i] == '+' && argument[i + 1] == '=')
			return (2);
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
		return (print_export(exec_struct->envp_struct));
	while (arguments)
	{
		if (!strcmp(arguments->argument, "_") \
		|| !strncmp(arguments->argument, "_=", 2) \
		|| !strncmp(arguments->argument, "_+=", 3))
			return ;
		if (is_alpha(arguments->argument) == 1)
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(arguments->argument, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exec_struct->command_line->current_exit_code = 1;
		}
		else if (is_alpha(arguments->argument) == 2)
			add2_export(exec_struct, arguments->argument);
		else
			add_export(exec_struct, arguments->argument);
		arguments = arguments->next;
	}
}
