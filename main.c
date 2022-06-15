#include "main.h"

/**
 * main - main program
 * @ac: arguments
 * @av: argument vector
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	info_shell datahsh;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datahsh, av);
	shell_loop(&datahsh);
	free_data(&datahsh);
	if (datahsh.status < 0)
		return (255);
	return (datahsh.status);
}
