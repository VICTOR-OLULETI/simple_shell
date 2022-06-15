#include "main.h"

/**
 * in_currdir - checks if ":" is in current directory
 * @path: path
 * @i: index
 * Return: 1 if path can be checked, 0 otherwise.
 */
int in_currdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);
	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}
	if (path[*i])
		*i += 1;
	return (0);
}

/**
 * is_executable - determines if an executable
 * @datahsh: data.
 * Return: 0 if not executable.
 */
int is_executable(info_shell *datahsh)
{
	struct stat st;
	int i;
	char *input;

	input = datahsh->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
		return (i);

	get_error(datahsh, 127);
	return (-1);
}

/**
 * check_access - checks if user has permission to access
 * @dir: directory destination
 * @datahsh: data
 * Return: 1 if error, or 0 
 */
int check_access(char *dir, info_shell *datahsh)
{
	if (dir == NULL)
	{
		get_error(datahsh, 127);
		return (1);
	}
	if (_strcmp(datahsh->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datahsh, 127);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datahsh->args[0], X_OK) == -1)
		{
			get_error(datahsh, 126);
			return (1);
		}
	}
	return (0);
}
