#include "minishell.h"

void 	print_arr(char **arr)
{
	while (arr && *arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}


