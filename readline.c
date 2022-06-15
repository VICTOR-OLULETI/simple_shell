#include "main.h"

/**
 * read_line - read the input string
 * @i: number of characters read
 *
 * Return: input
 */

char *read_line(int *i)
{
	char *input = NULL;
	size_t buffsize = 0;

	*i = getline(&input, &buffsize, stdin);
	return (input);
}
