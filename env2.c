#include "main.h"

/**
 * copy_info - copies information to create a new
 * env or alias.
 * @name: name of env or alias.
 * @value: value of env or alias.
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}
/**
 * set_env - sets an environmentt variable
 * @name: name of environment variable
 * @value: value of the environent variable
 * @datahsh: data
 * Return: void.
 */
void set_env(char *name, char *value, info_shell *datahsh)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datahsh->_environ[i]; i++)
	{
		var_env = _strdup(datahsh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datahsh->_environ[i]);
			datahsh->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	datahsh->_environ = _reallocdp(datahsh->_environ,
	i, sizeof(char *) * (i + 2));
	datahsh->_environ[i] = copy_info(name, value);
	datahsh->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names with name entered
 * as argument
 * @datahsh: data
 *
 * Return: 1 on success
 */
int _setenv(info_shell *datahsh)
{
	if (datahsh->args[1] == NULL || datahsh->args[2] == NULL)
	{
		get_error(datahsh, -1);
		return (1);
	}
	set_env(datahsh->args[1], datahsh->args[2], datahsh);

	return (1);
}

/**
 * _unsetenv - deletes an environment variable
 * @datahsh: data
 *
 * Return: 1 on success
 */
int _unsetenv(info_shell *datahsh)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datahsh->args[1] == NULL)
	{
		get_error(datahsh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datahsh->_environ[i]; i++)
	{
		var_env = _strdup(datahsh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datahsh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datahsh, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datahsh->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datahsh->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datahsh->_environ[k]);
	free(datahsh->_environ);
	datahsh->_environ = realloc_environ;
	return (1);
}
