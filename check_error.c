#include "main.h"

/**
 * repetition - records the number of occurence of a character
 * @input: input string
 * @index: index
 * Return: num of repitition
 */
int repetition(char *input, int index)
{
	if (*(input - 1) == *input)
		return (repetition(input - 1, index + 1));
	return (index);
}

/**
 * error_sep - looks for errors
 *
 * @input: input
 * @index: index
 * @last_read: char read last
 * Return: index if errors or 0 if none.
 */
int error_sep(char *input, int index, char last_read)
{
	int record;

	record = 0;
	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (error_sep(input + 1, index + 1, last_read));
	if (*input == ';')
		if (last_read == '|' || last_read == '&' || last_read == ';')
			return (index);

	if (*input == '|')
	{
		if (last_read == ';' || last_read == '&')
			return (index);
		if (last_read == '|')
		{
			record = repetition(input, 0);
			if (record == 0 || record > 1)
				return (index);
		}
	}
	if (*input == '&')
	{
		if (last_read == ';' || last_read == '|')
			return (index);
		if (last_read == '&')
		{
			record = repetition(input, 0);
			if (record == 0 || record > 1)
				return (index);
		}
	}
	return (error_sep(input + 1, index + 1, *input));
}
