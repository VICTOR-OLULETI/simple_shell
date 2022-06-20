#include "main.h"

/**
 * error_env - error messages for env
 * @datahsh: data
 *
 * Return: error
 */
char *error_env(info_shell *datahsh)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = _itoa(datahsh->counter);
	msg = ": Unable to add or remove from environment\n";
	length = _strlen(datahsh->av[0]) + _strlen(ver_str);
	length += _strlen(datahsh->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission.
 * @datahsh: data
 *
 * Return: error string
 */

char *error_path_126(info_shell *datahsh)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = _itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(ver_str);
	length += _strlen(datahsh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
