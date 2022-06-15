#include "main.h"

/**
 * shell_exit - exit the shell
 * @datahsh: data
 * Return: 0 on success.
 */
int shell_exit(info_shell *datahsh)
{
	unsigned int un_status;
	int is_digit, str_len, num;

	if (datahsh->args[1] != NULL)
	{
		un_status = _atoi(datahsh->args[1]);
		is_digit = _isdigit(datahsh->args[1]);
		str_len = _strlen(datahsh->args[1]);
		num = un_status > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || num)
		{
			get_error(datahsh, 2);
			datahsh->status = 2;
			return (1);
		}
		datahsh->status = (un_status % 256);
	}
	return (0);
}
