#include "linked_list_utils.h"

void	free_all_command_line(t_command_line **command_line)
{
	if (*command_line)
	{
		if ((*command_line)->substrings)
			free_substring(&(*command_line)->substrings);
		command_line = free_and_null(*command_line);
	}
}