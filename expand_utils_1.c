#include "minishell.h"

size_t	get_len_and_extract_between_single_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;

	len = 0;
	len_to_next_single_quote = strcspn(str, "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote);//malloc à protéger
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_with_single_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_single_quote;

	len = 0;
	len_to_next_single_quote = strcspn(&str[1], "\'");
	*extracted_line = ft_substr(str, 0, len_to_next_single_quote + 2);//malloc à protéger
	len = len_to_next_single_quote + 2;
	return (len);
}

size_t	get_len_and_extract_between_double_quotes(char *str, \
char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_double_quote;

	len = 0;
	len_to_next_double_quote = strcspn(str, "\"");
	*extracted_line = ft_substr(str, 0, len_to_next_double_quote);//malloc à protéger
	len = len_to_next_double_quote + 2;
	return (len);
}

size_t	get_len_and_extract_until_next_quote(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_quote;

	len_to_next_quote = strcspn(str, "\"\'");
	*extracted_line = ft_substr(str, 0, len_to_next_quote);//malloc à protéger
	len = len_to_next_quote;
	return (len);
}

size_t	get_len_and_extract_until_next_dollar(char *str, char **extracted_line)
{
	size_t	len;
	size_t	len_to_next_dollar;

	len_to_next_dollar = strcspn(str, "$");
	*extracted_line = ft_substr(str, 0, len_to_next_dollar);//malloc à protéger
	len = len_to_next_dollar;
	return (len);
}
