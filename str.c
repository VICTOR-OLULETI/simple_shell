#include "main.h"

/**
 * _strcat- concatenates string
 * @dest: first string
 * @src: second string
 *
 * Return: concatenated string
 */

char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j]; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy- copies second string to first string
 * @dest: first string
 * @src: second string
 *
 * Return: modified first string
 */

char *_strcpy(char *dest, char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
		dest[a] = src[a];
	dest[a] = '\0';
	return (dest);
}
/**
 * _strcmp- compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 on success
 */

int _strcmp(char *s1, char *s2)
{
	unsigned int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a character in a string.
 * @s: string
 * @c: character searched for.
 *
 * Return: pointer to the character sought for
 */

char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		if (*(s + i) == c)
			return (s + i);
	}
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}

/**
 * _strspn - gets th length of a prefix substring
 * @s: first string.
 * @accept: string to be compared.
 *
 * Return: length of prefix
 */
int _strspn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				bool = 9;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
