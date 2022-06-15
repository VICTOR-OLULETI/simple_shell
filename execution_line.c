#include "main.h"

/**
 * get_builtin - gets builtin commands
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(info_shell *)
{
	builtin_t builtin[] = {
		{ "cdd", cd_shell },
		{ "helpp", get_help },
		{ "envv", _env },
		{ "setenvv", _setenv},
		{ "unsetenvv", _unsetenv },
		{ "exitt", shell_exit },
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
/**
 * _which - locates a command
 * @cmd: command name
 * @_environ: environment variable
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
 * cmd_exec - executes command line
 * @datahsh: data
 * Return: 1 on success.
 */
int cmd_exec(info_shell *datahsh)
{
	pid_t pd;
	pid_t wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datahsh);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(datahsh->args[0], datahsh->_environ);
		if (check_access(dir, datahsh) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(datahsh->args[0], datahsh->_environ);
		else
		{
			dir = datahsh->args[0];
			dirr = datahsh->args[0];
		}
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

/**
 * exect_line - checks for built in commands and other commands
 *
 * @datahsh: data
 * Return: 1 on success.
 */
int exect_line(info_shell *datahsh)
{
	int (*builtin)(info_shell *datahsh);

	if (datahsh->args[0] == NULL)
		return (1);
	builtin = get_builtin(datahsh->args[0]);
	if (builtin != NULL)
		return (builtin(datahsh));
	return (cmd_exec(datahsh));
}
