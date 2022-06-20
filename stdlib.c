#include "main.h"

/**
 * get_len -gets length of a num
 * @num: integer number
 *
 * Return: length of a number
 */
int get_len(int num)
{
	unsigned int n1;
	int length = 1;

	if (num < 0)
	{
		length++;
		n1 = num * -1;
	}
	else
	{
		n1 = num;
	}
	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}
	return (length);
}
/**
 * _itoa - converts int to string
 * @num: int number
 *
 * Return: stringified number
 */
char *_itoa(int num)
{
	unsigned int n1;
	int length;
	char *buffer;

	length = get_len(num);
	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';
	if (num < 0)
	{
		n1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = num;
	}
	length--;
	do {
		*(buffer + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	}
	while (n1 > 0)
		;
	return (buffer);
}
/**
 * _atoi - converts string to integer
 * @s: input string
 *
 * Return: integer value.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;
		if (*(s + count) == '-')
			pn *= -1;
		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}
	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
