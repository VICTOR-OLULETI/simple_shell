#include "main.h"

/**
 * rev_string - reverses a string
 * @s: input string
 * Return: no return.
 */
void rev_string(char *s)
{
	int len = 0, i;
	char *str, temp;

	while (s[len])
	{
		len++;
	}
	str = s;
	for (i = 0; i < len / 2; i++)
	{
		temp = str[len - i - 1];
		str[len - i - 1] = str[i];
		str[i] = temp;
	}
}
