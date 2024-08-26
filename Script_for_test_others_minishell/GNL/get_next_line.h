/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:43:48 by ppuivif           #+#    #+#             */
/*   Updated: 2024/01/29 15:16:15 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
void	*ft_get_calloc(size_t nmemb, size_t size);
int		ft_get_strlen(char *s);
char	*ft_get_strjoin(char *s1, char *s2);
int		find_line_return(char *s);
char	*close_current_line(char *s1);
char	*begin_new_line(char *s1);

#endif
