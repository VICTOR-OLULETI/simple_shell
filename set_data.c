#include "main.h"

/**
 * get_sigint - handles ctrl + c when entered
 * sig: signal handler
 * Return: void.
 */
void get_sigint(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}

/**
 * set_data - sets data
 * @datahsh: linked list
 * @av: argument variable
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
 * free_data - frees data
 * @datahsh: linked list
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
