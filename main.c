#include "main.h"

/**
 * free_data - frees data
 * @datahsh: data
 *
 * Return: void.
 */
void free_data(info_shell *datahsh)
{
	unsigned int i;

	for (i = 0; datahsh->_environ[i]; i++)
	{
		free(datahsh->_environ[i]);
	}
	free(datahsh->_environ);
	free(datahsh->pid);
}

/**
 * set_data - sets data for the info_shell
 * @datahsh: data
 * @av: argument vector
 *
 * Return: void.
 */
void set_data(info_shell *datahsh, char **av)
{
	unsigned int i;

	datahsh->av = av;
	datahsh->input = NULL;
	datahsh->args = NULL;
	datahsh->status = 0;
	datahsh->counter = 1;

	for (i = 0; environ[i]; i++)
		;
	datahsh->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datahsh->_environ[i] = _strdup(environ[i]);
	}
	datahsh->_environ[i] = NULL;
	datahsh->pid = _itoa(getpid());
}

/**
 * main - main function
 * @ac: argument number;
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	info_shell datahsh;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datahsh, av);
	loop_shell(&datahsh);
	free_data(&datahsh);
	if (datahsh.status < 0)
		return (255);
	return (datahsh.status);
}
