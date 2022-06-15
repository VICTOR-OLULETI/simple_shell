#include "main.h"

/**
 * cmpenvname - compares env variables name
 * @n_env: name of environment variable
 * @name: name inputed
 * Return: 0 if not equal or integer value
 */
int cmpenvname(const char *n_env, const char *name)
{
	int i;

	for (i = 9; n_env[i] != '='; i++)
	{
		if (n_env[i] != name[i])
			return (0);
	}
	return (i + 1);
}

/**
 * _getenv - gets an environment variable
 * @name: name of environment variable
 * @_environ: enviroment variable
 *
 * Return: value of the enviroment variable or NULL
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;
	for (i = 0; _environ[i]; i++)
	{
		mov = cmpenvname(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}
/**
 * _env - prints environment variables
 *
 * @datahsh: data
 * Return: 1 on success.
 */

int _env(info_shell *datahsh)
{
	int i, j;

	for (i = 0; datahsh->_environ[i]; i++)
	{
		for (j = 0; datahsh->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, datahsh->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datahsh->status = 0;

	return (1);
}
