#include "main.h"

/**
 * in_currdir - checks for ":" in current directory
 * @path: path
 * @i: integer
 *
 * Return: 1 if path or 0 if failure
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
 * _which - locates command
 *
 * @cmd: command name
 * @_environ: environement variable
 *
 * Return: where command is located
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (in_currdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * is_exec - checks if executable
 * @datahsh: data
 * Return: if not execuable return 0 else integer number
 */
int is_exec(info_shell *datahsh)
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
	{
		return (i);
	}
	get_error(datahsh, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies permission to access
 * @dir: directory
 * @datahsh: data
 * Return: 1 if error, 0 if not.
 */
int check_error_cmd(char *dir, info_shell *datahsh)
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
			get_error(datahsh, 126);
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

/**
 * cmd_exec - executes command line
 * @datahsh: data
 *
 * Return: 1 on success.
 */
int cmd_exec(info_shell *datahsh)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_exec(datahsh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datahsh->args[0], datahsh->_environ);
		if (check_error_cmd(dir, datahsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datahsh->args[0], datahsh->_environ);
		else
			dir = datahsh->args[0];
		execve(dir + exec, datahsh->args, datahsh->_environ);
	}
	else if (pd < 0)
	{
		perror(datahsh->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	datahsh->status = state / 256;
	return (1);
}
