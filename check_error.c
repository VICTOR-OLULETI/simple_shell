#include "main.h"

/**
 * repetition - counts repetition of characters
 *
 * @input_str: input string
 * @i: index
 * Return: index
 */
int repetition(char *input_str, int i)
{
	if (*(input_str - 1) == *input_str)
		return (repetition(input_str - 1, i + 1));
	return (i);
}

/**
 * error_sep - finds errors (syntax)
 *
 * @input: input string
 * @i: index
 * @last: last read char
 * Return: index of error. 0 if no error
 */
int error_sep(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (error_sep(input + 1, i + 1, last));
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);
	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);
		if (last == '|')
		{
			count = repetition(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);
		if (last == '&')
		{
			count = repetition(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep(input + 1, i + 1, *input));
}

/**
 * char_first - finds index of first character
 * @input: input string
 * @i: index
 * Return: 1 if error and 0 if not.
 */
int char_first(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;
		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);
		break;
	}
	return (0);
}
/**
 * print_error - prints error when found
 *
 * @datahsh: data
 * @input: input string
 * @i: index
 * @bool: 0 or 1
 *
 * Return: void
 */

void print_error(info_shell *datahsh, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i + 1] == ';' ? ";;" : ";");
	}
	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");
	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");
	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_error - function to find and
 * print a syntax error
 * @datahsh: data
 * @input: input string
 *
 * Return: 1 if error
 */
int check_error(info_shell *datahsh, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = char_first(input, &begin);
	if (f_char == -1)
	{
		print_error(datahsh, input, begin, 0);
		return (1);
	}

	i = error_sep(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_error(datahsh, input, begin + i, 1);
		return (1);
	}
	return (0);
}
