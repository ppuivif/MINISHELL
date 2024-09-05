/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:41 by drabarza          #+#    #+#             */
/*   Updated: 2024/09/05 08:36:12 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_line(char *envp, t_envp_struct **envp_struct)
{
	t_envp_struct	*new_element;

	new_element = NULL;
	init_envp_struct(&new_element);
	new_element->name = ft_substr(envp, 0, ft_strcspn(envp, "="));
	if (!new_element->name)
		error_allocation_envp_struct_and_exit(envp_struct);
	if (ft_strcspn(envp, "=") < (int)ft_strlen(envp))
		new_element->equal = 1;
	else
		new_element->equal = 0;
	new_element->value = ft_substr(envp, ft_strcspn(envp, "=") + 1, \
		ft_strlen(envp));
	if (!new_element->value)
		error_allocation_envp_struct_and_exit(envp_struct);
	ft_lst_add_back6(envp_struct, new_element);
}

static void	search_variables(t_envp_struct **envp_struct)
{
	char	str[PATH_MAX];
	char	*pwd;

	pwd = NULL;
	getcwd(str, PATH_MAX);
	if (search_var(*envp_struct, "PWD") == 0)
	{
		pwd = ft_strjoin("PWD=", str);
		add_line(pwd, envp_struct);
	}
	if (search_var(*envp_struct, "SHLVL") == 0)
		add_line("SHLVL=1", envp_struct);
	if (search_var(*envp_struct, "OLDPWD") == 0)
		add_line("OLDPWD", envp_struct);
}

void	get_envp(char **envp, t_envp_struct **envp_struct)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_line(envp[i], envp_struct);
		i++;
	}
	search_variables(envp_struct);
}
