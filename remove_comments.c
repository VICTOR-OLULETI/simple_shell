#include "main.h"

/**
 * without_comment - rmoves comments
 * @input: input string
 *
 * Return: return input without comments
 */

char *without_comment(char *input)
{
	int i, till;

	till = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}
			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				till = i;
		}
	}
	if (till != 0)
	{
		input = _realloc(input, i, till + 1);
	       input[till] = '\0';
	}
	return (input);
}
