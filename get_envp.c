#include "minishell.h"

static void	add_line(char *envp, t_envp_struct **envp_struct)
{
	t_envp_struct	*new_element;

	new_element = NULL;
	if (init_envp_struct(&new_element) == -1)
		error_allocation_envp_struct();
	new_element->content = ft_strdup(envp);
	ft_lst_add_back6(envp_struct, new_element);
}

void	get_envp(char **envp, t_envp_struct **envp_struct)
{
	int	i;

	i = 0;
	if (!envp || !envp[0])
	{
		ft_putstr_fd("error\nenvp doesn't exists or is empty\n", 2);
		exit(EXIT_FAILURE);
	}
	while (envp[i])
	{
		add_line(envp[i], envp_struct);
		i++;
	}
}

void	free_envp(t_envp_struct **envp_struct)
{
	t_envp_struct	*tmp;

	while (ft_lst_size6(*envp_struct))
	{
		tmp = (*envp_struct)->next;
		free((*envp_struct)->content);
		free(*envp_struct);
		*envp_struct = NULL;
		*envp_struct = tmp;
	}
}
