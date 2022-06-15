#include "main.h"

/**
 * strcat_cd - concatenates message for cd error
 * @datahsh: data
 * @msg: message to pring.
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */

char *strcat_cd(info_shell *datahsh, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, msg);
	if (datahsh->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datahsh->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datahsh->args[1]);
	}
	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - error messagefor cd commands in get_cd
 * @datahsh: data
 * Return: error message
 */
char *error_get_cd(info_shell *datahsh)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = _itoa(datahsh->counter);
	if (datahsh->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datahsh->args[1]);
	}

	length = _strlen(datahsh->av[0]) + _strlen(datahsh->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datahsh, msg, error, ver_str);
	free(ver_str);
	return (error);
}

/**
 * error_not_found - error message for command not found
 * @datahsh: dat
 * Return: error message
 */
char *error_not_found(info_shell *datahsh)
{
	int length;
	char *error, *ver_str;

	ver_str = _itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(ver_str);
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_shell_exit - error message for exit in get_exit
 * @datahsh: data
 * Return: error message
 */
char *error_shell_exit(info_shell *datahsh)
{
	int length;
	char *error, *ver_str;

	ver_str = _itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(ver_str);
	length += _strlen(datahsh->args[0]) + _strlen(datahsh->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datahsh->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
