#include "main.h"

/**
 * exect_line - finds builtin function commands
 * @datahsh: data
 *
 * Return: 1 on success.
 */
int exect_line(info_shell *datahsh)
{
	int (*builtin)(info_shell *datahsh);

	if (datahsh->args[0] == NULL)
		return (1);
	builtin = get_builtin(datahsh->args[0]);

	if (builtin != NULL)
		return (builtin(datahsh));

	return (cmd_exec(datahsh));
}
