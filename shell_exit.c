#include "main.h"

/**
 * shell_exit - exits the shell
 * @datahsh: data
 *
 * Return: 0 on succes.
 */
int shell_exit(info_shell *datahsh)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int num;

	if (datahsh->args[1] != NULL)
	{
		ustatus = _atoi(datahsh->args[1]);
		is_digit = _isdigit(datahsh->args[1]);
		str_len = _strlen(datahsh->args[1]);
		num = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || num)
		{
			get_error(datahsh, 2);
			datahsh->status = 2;
			return (1);
		}
		datahsh->status = (ustatus % 256);
	}
	return (0);
}
