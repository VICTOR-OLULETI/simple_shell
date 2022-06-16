#include "main.h"

/**
 * get_help - retrieves help message according builtin
 * @datahsh: data
 * Return: 0 in success.
 */
int get_help(info_shell *datahsh)
{
	if (datahsh->args[1] == 0)
		help_general();
	else if (_strcmp(datahsh->args[1], "setenv") == 0)
		help_setenv();
	else if (_strcmp(datahsh->args[1], "env") == 0)
		help_env();
	else if (_strcmp(datahsh->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(datahsh->args[1], "help") == 0)
		_help();
	else if (_strcmp(datahsh->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(datahsh->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(datahsh->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, datahsh->args[0],
			_strlen(datahsh->args[0]));
	datahsh->status = 0;
	return (1);
}
