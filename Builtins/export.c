/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:23:13 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 14:57:28 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	search_var(t_exec_struct *exec_struct, char *str)
{
	t_envp_struct	*env;

	env = exec_struct->envp_struct;
	while (env)
	{
		if (!strcmp(env->name, str))
			return (1);
		env = env->next;
	}
	return (0);
}

static void	add_export(t_exec_struct *exec_struct, \
	char *argument)
{
	t_envp_struct	*env;	
	int				len_name;
	char			*tmp1;
	char			*tmp2;

	env = exec_struct->envp_struct;
	len_name = ft_strcspn(argument, "=");
	if (len_name == 0)
	{
		if (search_var(exec_struct, argument))
			return ;
		tmp1 = ft_substr(argument, 0, ft_strlen(argument));
		ft_lst_add_back6(&exec_struct->envp_struct, ft_lstnew \
			(tmp1, NULL, 0));
		free(tmp1);
		tmp1 = NULL;
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
	tmp1 = ft_substr(argument, 0, len_name);
	tmp2 = ft_substr(argument, len_name + 1, ft_strlen(argument));
	ft_lst_add_back6(&exec_struct->envp_struct, \
	ft_lstnew(tmp1, tmp2, 1));
	free(tmp1);
	tmp1 = NULL;
	free(tmp2);
	tmp2 = NULL;
}

static void	add2_export(t_exec_struct *exec_struct, \
	char *argument)
{
	t_envp_struct	*env;	
	int				len_name;
	char			*temp;

	env = exec_struct->envp_struct;
	len_name = ft_strcspn(argument, "=");
	if (len_name == 0)
	{
		if (!search_var(exec_struct, argument))
			ft_lst_add_back6(&exec_struct->envp_struct, ft_lstnew \
				(ft_substr(argument, 0, ft_strlen(argument)), NULL, 0));
		return ;
	}
	while (env)
	{
		if (!ft_strncmp(env->name, argument, len_name - 1))
		{
			temp = ft_strdup_freed(env->value);
			env->value = ft_strjoin_freed(temp, \
			ft_substr(argument, len_name + 1, ft_strlen(argument)));
			env->equal = 1;
			return ;
		}
		env = env->next;
	}
	env = exec_struct->envp_struct;
	ft_lst_add_back6(&exec_struct->envp_struct, \
	ft_lstnew(ft_substr(argument, 0, len_name - 1), \
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
	{
		print_export(exec_struct->envp_struct);
		return ;
	}
	while (arguments)
	{
		if (!strcmp(arguments->argument, "_") || !strncmp(arguments->argument, "_=", 2) || !strncmp(arguments->argument, "_+=", 3))
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
