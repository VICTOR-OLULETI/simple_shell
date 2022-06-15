#include "main.h"

/**
 * char_swap - swaps ||  and & for nonprinted characters
 * @input: input string
 * @bool: bool helps to control swapping
 * Return: string swapped
 */
char *char_swap(char *input, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == '|')
			{
				if (input[j + 1] != '|')
					input[j] = 16;
				else
					j++;
			}

			if (input[j] == '&')
			{
				if (input[j + 1] != '&')
					input[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; input[j]; j++)
		{
			input[j] = (input[j] == 16 ? '|' : input[j]);
			input[j] = (input[j] == 12 ? '&' : input[j]);
		}
	}
	return (input);
}

