#include "main.h"

/**
 * get_builtin - retrieves builtin  command
 * @cmd: command name
 * Return: function pointer to builtin command
 */
int (*get_builtin(char *cmd))(info_shell *)
{
	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", shell_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", cd_shell },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
