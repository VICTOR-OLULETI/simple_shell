#include "main.h"

/**
 * char_first - index of first character
 *
 * @input: input
 * @index: index
 * Return: -1 if error or 0 if not.
 */
int char_first(char *input, int *index)
{
	for(*index = 0; input[*index]; *index += 1)
	{
		if (input[*index] ==' ' || input[*index] == '\t')
			continue;
		if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
			return (-1);
		break;
	}

	return (0);
}
