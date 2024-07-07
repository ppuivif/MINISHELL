#include "minishell.h"

int	is_pipe_latest_character(char **remaining_line)
{
	if (*remaining_line[0] && *remaining_line[0] == '|')
	{
		(*remaining_line)++;
		*remaining_line = skip_first_whitespaces(*remaining_line);
		if (ft_strlen(*remaining_line) == 0)
			return (true);
		return (false);
	}
	else
		return (false);
}

int	is_pipe_first_character(char *remaining_line)
{
	if (remaining_line[0] && remaining_line[0] == '|')
		return (true);
	else
		return (false);
}

int	check_char_validity(char *remaining_line, int len_to_quote, int flag, int j)
{
	int len_to_end;

	len_to_end = (int)ft_strlen(&remaining_line[1]);
	if (!remaining_line[len_to_quote + flag + j] || (len_to_quote + flag + j) > (len_to_end + 1))
		return (-1);
	if (remaining_line[len_to_quote + flag + j] == '>' || \
	remaining_line[len_to_quote + flag + j] == '|' || \
	ft_isspace(remaining_line[len_to_quote + flag + j]) == true)
		return (-1);
	else
		return(0);
}

unsigned int count_angled_bracket(char *str)
{
	unsigned int nmemb;

	nmemb = 0; 
	while(str && (*str == '<' || *str == '>' || ft_isspace(*str) == true))
	{
		if (*str == '<' || *str == '>')
		nmemb++;
		str++;
	}
	return (nmemb);
}
