#include "main.h"

/**
 * get_line - reads input from stream
 * @linep: buff stores the inut
 * @n: size of linp
 * @stream: stream to read from
 * Return: number of bytes
 */
ssize_t get_line(char **linep, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buff;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buff = malloc(sizeof(char) * BUFSIZE);
	if (buff == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buff);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buff = _realloc(buff, input, input + 1);
		buff[input] = t;
		input++;
	}
	buff[input] = '\0';
	sets_line(linep, n, buff, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

