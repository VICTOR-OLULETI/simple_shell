#include "main.h"

/**
 * _help - Help information for the bultin help.
 * Return: void.
 */
void _help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands. \n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * help_alias - Help information for the builfin alias.
 * Return: void.
 */
void help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases. \n ";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * help_cd - Help information for the builtins
 * Return: void.
 */
void help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
