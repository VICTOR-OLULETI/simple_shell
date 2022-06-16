#include "main.h"

/**
 * cd_shell - changes current directory
 * @datahsh: data
 * Return: 1 on success
 */

int cd_shell(info_shell *datahsh)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datahsh->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}
	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(datahsh);
		return (1);
	}
	if (_strcmp("-", dir) == 0)
	{
		cd_prev(datahsh);
		return (1);
	}
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datahsh);
		return (1);
	}
	cd_to(datahsh);

	return (1);
}
