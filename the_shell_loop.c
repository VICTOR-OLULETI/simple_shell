#include "main.h"


/**
 * loop_shell - the shell loop to run continuously
 * @datahsh: linked list containing (av, input, args).
 *
 * Return: void.
 */
void loop_shell(info_shell *datahsh)
{
	int loop, i;
	char *input_str;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input_str = read_line(&i);
		if (i != -1)
		{
			input_str = remove_comment(input_str);
			if (input_str == NULL)
				continue;
			if (check_error(datahsh, input_str) == 1)
			{
				datahsh->status = 2;
				free(input_str);
				continue;
			}
			input_str = replace_var(input_str, datahsh);
			loop = split_commands(datahsh, input_str);
			datahsh->counter += 1;
			free(input_str);
		}
		else
		{
			loop = 0;
			free(input_str);
		}
	}
}

/**
 * remove_comment - deletes comments from input
 * @in: input string
 *
 * Return: input string without comments
 */

char *remove_comment(char *in)
{
	int i, till;

	till = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t'
				|| in[i - 1] == ';')
				till = i;
		}
	}
	if (till != 0)
	{
		in = _realloc(in, i, till + 1);
		in[till] = '\0';
	}
	return (in);
}
