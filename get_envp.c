#include "minishell.h"

static void add_line(char *envp, t_envp_struct **envp_struct)
{
	t_envp_struct	*new_element;

	new_element = NULL;
	if (init_envp_struct(&new_element) == -1)
		error_allocation_envp_struct(envp_struct);
	new_element->content = ft_strdup(envp);
	ft_lst_add_back6(envp_struct, new_element);
}

void get_envp(char **envp, t_envp_struct **envp_struct)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_line(envp[i], envp_struct);
		i++;
	}
}


