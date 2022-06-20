#include "main.h"

/**
 * read_line - reads input string.
 *
 * @i: return getline function
 * Return: input string
 */
char *read_line(int *i)
{
	char *input_str = NULL;
	size_t bufsize = 0;

	*i = getline(&input_str, &bufsize, stdin);

	return (input_str);
}
