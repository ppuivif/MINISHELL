/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drabarza <drabarza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:32:14 by drabarza          #+#    #+#             */
/*   Updated: 2024/08/20 14:58:07 by drabarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	print_arr(char **arr)
{
	int	pid;

	pid = fork();
	open("infile", O_RDONLY);
	while (1)
	{
		printf("Helloo miniHELL %i\n", pid);
		sleep(1);
	}
	return (0);
}
