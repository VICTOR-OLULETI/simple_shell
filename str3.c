#include "main.h"

/**
 * rev_string - reverses a string
 * @s: input string
 * Return: no return.
 */
void rev_string(char *s)
{
	int len = 0, i, j;
	char *str, temp;

	while (s[len])
	{
		len++;
	}
	str = s;
	for (i = 0; i < len / 2; i++)
	{
		temp = s[len - i - 1];
		s[len - i - 1] = s[i];
		s[i] = temp;
	}
}

