#include "main.h"

/**
 * get_error - retrieves error due to builtin, syntax or permission
 * @datahsh: data
 * @eval: error value
 * Return: error.
 */
int get_error(info_shell *datahsh, int eval)
{
	char *error;

	switch (eval)
	{
		case -1:
			error = error_env(datahsh);
			break;
		case 126:
			error = error_path_126(datahsh);
			break;
		case 127:
			error = error_not_found(datahsh);
			break;
		case 2:
			if (_strcmp("exit", datahsh->args[0]) == 0)
				error = error_shell_exit(datahsh);
			else if (_strcmp("cd", datahsh->args[0]) == 0)
				error = error_get_cd(datahsh);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datahsh->status = eval;
	return (eval);
}
