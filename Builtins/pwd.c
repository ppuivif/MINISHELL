/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:30:07 by drabarza          #+#    #+#             */
/*   Updated: 2024/06/27 13:19:45 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include "minishell.h"

int	pwd(void)
{
	char	str[PATH_MAX];
	
	if (getcwd(str, PATH_MAX))
		printf("%s\n", str);
	else
		return (errno);
	return (1);
}

/* int	main(void)
{
	pwd();
	return (0);
} */
