/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:50:21 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/04 16:15:48 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(t_envp_struct *envp_struct, char *str)
{
	t_envp_struct	*env;

	env = envp_struct;
	while (env)
	{
		if (!ft_strcmp(env->name, str))
			return (1);
		env = env->next;
	}
	return (0);
}

static void	new_export(t_exec_struct *exec_struct, \
	char *argument, int len_name, int i)
{
	char			*tmp1;
	char			*tmp2;

	tmp1 = ft_substr(argument, 0, len_name - i);
	tmp2 = ft_substr(argument, len_name + 1, ft_strlen(argument));
	ft_lst_add_back6(&exec_struct->envp_struct, \
	ft_lstnew(tmp1, tmp2, 1));
	free(tmp1);
	tmp1 = NULL;
	free(tmp2);
	tmp2 = NULL;
}

static void	new_name_export(t_exec_struct *exec_struct, \
	char *argument)
{
	char	*tmp1;

	if (search_var(exec_struct->envp_struct, argument))
		return ;
	tmp1 = ft_substr(argument, 0, ft_strlen(argument));
	ft_lst_add_back6(&exec_struct->envp_struct, ft_lstnew \
		(tmp1, NULL, 0));
	free(tmp1);
	tmp1 = NULL;
}

void	add_export(t_exec_struct *exec_struct, char *argument)
{
	t_envp_struct	*env;	
	int				len_name;

	env = exec_struct->envp_struct;
	len_name = ft_strcspn(argument, "=");
	if (len_name == (int)ft_strlen(argument))
	{
		new_name_export(exec_struct, argument);
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
	new_export(exec_struct, argument, len_name, 0);
}

void	add2_export(t_exec_struct *exec_struct, char *argument)
{
	t_envp_struct	*env;
	int				len_name;
	char			*tmp1;
	char			*tmp2;

	env = exec_struct->envp_struct;
	len_name = ft_strcspn(argument, "=");
	while (env)
	{
		if (!ft_strncmp(env->name, argument, len_name - 1))
		{
			tmp1 = ft_strdup_freed(env->value);
			tmp2 = ft_substr(argument, len_name + 1, ft_strlen(argument));
			env->value = ft_strjoin_freed(tmp1, tmp2);
			env->equal = 1;
			free(tmp2);
			tmp2 = NULL;
			return ;
		}
		env = env->next;
	}
	new_export(exec_struct, argument, len_name, 1);
}
