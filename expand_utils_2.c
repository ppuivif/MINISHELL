#include "minishell.h"

size_t	get_len_and_extract_until_next_quote_or_dollar(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote_or_dollar;

	len_to_next_quote_or_dollar = strcspn(str, "$\"\'\0");
	*extracted_line = ft_substr(str, 0, len_to_next_quote_or_dollar);
	len = len_to_next_quote_or_dollar;
	return (len);
}

size_t	get_len_and_extract_until_next_separator(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(str, "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);
	len = len_to_next_separator;
	return (len);
}

size_t	get_len_and_extract_until_next_separator_dollar_excluded(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(str, "\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator);
	len = len_to_next_separator;
	return (len);
}

size_t	get_len_and_extract_after_first_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_separator;

	len_to_next_separator = strcspn(&str[1], "$\"\' \t\n\v\f\r\0");
	*extracted_line = ft_substr(str, 0, len_to_next_separator + 1);
	len = len_to_next_separator + 1;
	return (len);
}
