#include "main.h"

/**
 * sets_line - will assign line var to get_line
 * @linep: buff storing input string
 * @buff: string called
 * @n: size of line
 * @j: size of buff
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
