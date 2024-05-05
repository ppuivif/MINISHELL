#ifndef LIBFT_UTILS_H
# define LIBFT_UTILS_H	t_command.line = NULL;


# include <stdlib.h>
# include <unistd.h>

size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
unsigned int	search_first_occurence(char *str, char c);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strdup(const char *s);
char			*ft_strdup_freed(char *s);
//char			*extract_substring(char *str, char c);
char			*ft_substr(const char *s, unsigned int start, size_t len);
//char			*ft_strjoin_freed(char *s1, char *s2);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char const *s, char c);
void			ft_putnbr_fd(int n, int fd);
char			*skip_first_spaces(char *str);
void			*free_arr(char **arr);

#endif