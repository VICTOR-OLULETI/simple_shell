#include "main.h"

/**
 * env_check - checks for environment variable
 * @h: head of linked list
 * @input: input string
 * @data: data
 * Return: void
 */

void env_check(r_var **h, char *input, info_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}
		if (input[j] == _envr[row][chr])
			j++;
		else
			break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';'
		    || input[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}
