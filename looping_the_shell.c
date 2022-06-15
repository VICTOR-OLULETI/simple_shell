#include "main.h"

/**
 * shell_loop - loopint the shell
 * @datahsh: data
 *
 * Return: void.
 */
void shell_loop(info_shell *datahsh)
{
	int loopint, ieof;
	char *input;

	loopint = 1;
	while (loopint == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&ieof);
		if (ieof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;
			if (check_error(datahsh, input) == 1)
			{
				datahsh->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, datahsh);
			loopint = splits_command(datahsh, input);
			datahsh->counter += 1;
			free(input);
		}
		else
		{
			loopint = 0;
			free(input);
		}
	}
}
