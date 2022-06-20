#include "main.h"

/**
 * sets_line - assigning fof line var for get_line
 * @linep: buffer to store the string entered
 * @buff: string called
 * @n: size of command line argument
 * @j: size of buffer
 */
void sets_line(char **linep, size_t *n, char *buff, size_t j)
{
	if (*linep == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*linep = buff;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*linep = buff;
	}
	else
	{
		_strcpy(*linep, buff);
		free(buff);
	}
}

/**
 * get_line - read input from stream
 * @linep: buffer storing input.
 * @n: size of linep
 * @stream: stream read from
 *
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
