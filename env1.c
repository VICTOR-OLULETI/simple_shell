#include "main.h"

/**
 * cmpenvname - compares env variable names
 * @nenv: name of the environment variable
 * @name: name entered
 *
 * Return: 0 if unequal
 */
int cmpenvname(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
			return (0);
	}
	return (i + 1);
}
/**
 * _getenv - gets environment variablee
 * @name: name of environment variable
 * @_environ: environment variable
 *
 * Return: value of environment variable
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, move;

	ptr_env = NULL;
	move = 0;

	for (i = 0; _environ[i]; i++)
	{
		move = cmpenvname(_environ[i], name);
		if (move)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + move);
}

/**
 * _env - prints the env
 * @datahsh: data
 *
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
