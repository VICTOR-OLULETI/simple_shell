#include "main.h"

/**
 * splits_line - splits the input string into tokens
 * @input: input string
 * Return: string splitted.
 */
char **splits_line(char *input)
{
	size_t T_bsize, i;
	char **tokens;
	char *token;

	T_bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (T_bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;
	for (i = 1; token != NULL; i++)
	{
		if (i == T_bsize)
		{
			T_bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * T_bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}
	return (tokens);
}

/**
 * splits_command - splits command lines and executes them(;, |, &)
 * @datahsh: data
 * @input: input string
 * Return: 0 on exi or 1 to conitnue
 */
int splits_command(info_shell *datahsh, char *input)
{
	sep_list *h_s, *list_s;
	line_list *h_l, *list_l;
	int loop;

	h_s = NULL;
	h_l = NULL;

	add_nodes(&h_s, &h_l, input);

	list_s = h_s;
	list_l = h_l;

	while (list_l != NULL)
	{
		datahsh->input = list_l->line;
		datahsh->args = splits_line(datahsh->input);
		loop = exect_line(datahsh);
		free(datahsh->args);

		if (loop == 0)
			break;
		next_command(&list_s, &list_l, datahsh);
		if (list_l != NULL)
			list_l = list_l->next;
	}
	free_sep_list(&h_s);
	free_line_list(&h_l);
	if (loop == 0)
		return (0);
	return (1);
}
