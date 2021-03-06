#include "main.h"

/**
 * cd_dot - changes to parent directory
 * @datahsh: data
 * Return: void.
 */
void cd_dot(info_shell *datahsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datahsh);
	dir = datahsh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datahsh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datahsh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datahsh);
	}
	datahsh->status = 0;
	free(cp_pwd);
}
/**
 * cd_to - changes to given directory
 * @datahsh: data
 *
 * Return: void.
 */
void cd_to(info_shell *datahsh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datahsh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datahsh, 2);
		return;
	}
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datahsh);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datahsh);

	free(cp_pwd);
	free(cp_dir);

	datahsh->status = 0;
	chdir(dir);
}
/**
 * cd_prev - changes to previous directory
 * @datahsh: data
 *
 * Return: void.
 */
void cd_prev(info_shell *datahsh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datahsh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);
	set_env("OLDPWD", cp_pwd, datahsh);
	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datahsh);
	else
		set_env("PWD", cp_oldpwd, datahsh);

	p_pwd = _getenv("PWD", datahsh->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);
	datahsh->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes to home directory
 * @datahsh: data
 * Return: void.
 */
void cd_home(info_shell *datahsh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datahsh->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datahsh);
		free(p_pwd);
		return;
	}
	if (chdir(home) == -1)
	{
		get_error(datahsh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datahsh);
	set_env("PWD", home, datahsh);
	free(p_pwd);
	datahsh->status = 0;
}
