#include "main.h"

/**
 * help_general - help information for help builtin
 *
 * Return: void.
 */
void help_general(void)
{
	char *help = "cisfun# bash, version 1.0 - release\n";

	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * help_env - Help information for builtin env
 *
 * Return: void.
 */

void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * help_setenv - Help information for the builtin setenv
 *
 * Return: void.
 */
void help_setenv(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_unsetenv - Help information for the builtin unsetenv
 *
 * Return: void.
 */

void help_unsetenv(void)
{
	char *help = "cisfun# bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Type 'help name' to find out more.\n\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * help_exit - Help information for "exit".
 *
 * Return: void.
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell. \n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with status 'n'.";
	write(STDOUT_FILENO, help, _strlen(help));
}
