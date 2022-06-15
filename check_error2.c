#include "main.h"

/**
 * check_error - find and print error
 * @datahsh: data
 * @input: input
 * Return: 1 if error or 0 if not.
 */
int check_error(info_shell *datahsh, char *input)
{
	int start = 0, f_char = 0, i = 0;	

	f_char = char_first(input, &start);
	if (f_char == -1)
	{
		print_error(datahsh, input, start, 0);
		return (1);
	}
	i = error_sep(input + start, 0, *(input + start));
	if (i != 0)
	{
		print_error(datahsh, input, start + i, 1);
		return (1);
	}
	return (0);
}
