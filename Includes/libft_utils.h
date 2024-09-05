/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppuivif <ppuivif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:31:54 by ppuivif           #+#    #+#             */
/*   Updated: 2024/09/05 10:00:50 by ppuivif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>

/*
* libft_utils_1.c
*/

size_t			ft_strlen(const char *s);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcspn(char *remaining_line, char *str);
char			*skip_first_whitespaces(char *str);

/*
* libft_utils_2.c
*/

bool			ft_isspace(int c);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_substr(const char *s, unsigned int start, size_t len);

/*
* libft_utils_3.c
*/

char			*ft_strdup(const char *s);
char			*ft_strdup_freed(char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin_freed(char *s1, char *s2);

/*
* libft_utils_4.c
*/

char			**ft_split(char const *s, char c);

/*
* libft_utils_5.c
*/

char			*ft_itoa(int n);
int				ft_atoi(const char *nptr);

/*
* libft_utils_6.c
*/

void			close_fd(int fd);
void			*free_and_null(void *ptr);
char			**arr_copy(char **arr);
void			*free_arr(char **arr);

#endif