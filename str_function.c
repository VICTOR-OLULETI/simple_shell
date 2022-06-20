#include "main.h"

/**
 * _strcat - concatenates two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: concatenated first string
 */
char *_strcat(char *str1, const char *str2)
{
	int i, j;

	for (i = 0; str1[i] != '\0'; i++)
		;
	for (j = 0; str2[j] != '\0'; j++)
	{
		str1[i] = str2[j];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}
/**
 * *_strcpy - copies second string into the first
 * @str1: first string
 * @str2: second string
 *
 * Return: first string modified
 */

char *_strcpy(char *str1, char *str2)
{
	size_t a;

	for (a = 0; str2[a] != '\0'; a++)
	{
		str1[a] = str2[a];
	}
	str1[a] = '\0';

	return (str1);
}
/**
 * _strcmp - comapres two strings
 * @s1: first string
 * @s2: second string to be comapred with the first
 *
 * Return: Always 0.
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;
	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locating a character ina string
 * @s: string
 * @c: character
 *
 * Return: pointer to the first occurence of the character
 * in the string
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}
/**
 * _strspn - gets length of a prefix substring
 * @s: initial segment.
 * @accept: accepted bytes
 *
 * Return: number of accepted bytes
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
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
