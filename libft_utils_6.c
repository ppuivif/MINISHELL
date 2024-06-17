/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:08:21 by ppuivif           #+#    #+#             */
/*   Updated: 2024/06/17 16:38:57 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft_utils.h"

void	close_fd(int fd)
{
	if (fd && fd > 2 && fd != STDIN_FILENO && fd != STDOUT_FILENO)
		close(fd);
}
void	free_and_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}