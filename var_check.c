#include "main.h"

/**
 * var_check - check if variable is $$ or $
 * @h: head of linked list
 * @input: input string
 * @status: status of shell
 * @data: data
 * Return: void.
 */

int var_check(r_var **h, char *input, char *status, info_shell *data)
{
	int i, last_status, lpd;

	last_status = _strlen(status);
	lpd = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				add_rvar_node(h, 2, status, last_status), i++;
			else if (input[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (input[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				env_check(h, input + i, data);
		}
	}
	return (i);
}
