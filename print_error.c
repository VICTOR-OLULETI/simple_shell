#include "main.h"

/**
 * print_error - prints syntax error message
 *
 * @datahsh: data
 * @input: input
 * @index: index of error
 * @bool: state of errr message
 * Return: void.
 */

void print_error(info_shell *datahsh, char *input, int index, int bool)
{
	char *message, *message2, *message3, *error_msg, *counter;
	int length;

	if (input[index] == ';')
	{
		if (bool == 0)
			message = (input[index + 1] == ';' ? ";;" : ";");
		else
			message = (input[index - 1] == ';' ? ";;" : ";");
	}

	if (input[index] == '|')
		message = (input[index + 1] == '|' ? "||" : "|");
	if (input[index] == '&')
		message = (input[index + 1] == '&' ? "&&" : "&");
	message2 = ": Syntax error: \"";
	message3 = "\" unexpected\n";
	counter = _itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(counter);
	length += _strlen(message) + _strlen(message2) + _strlen(message3) + 2;

	error_msg = malloc(sizeof(char) * (length + 1));
	if (error_msg == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error_msg, datahsh->av[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, counter);
	_strcat(error_msg, message2);
	_strcat(error_msg, message);
	_strcat(error_msg, message3);
	_strcat(error_msg, "\0");
	write(STDERR_FILENO, error_msg, length);
	free(error_msg);
	free(counter);
}
