#include "main.h"

/**
 * split_commands - splits command lines by separators ;, | and &
 * and executes it
 * @datahsh: data
 * @input: input string
 *
 * Return: 0 to exit, 1 to continue
 */
int split_commands(info_shell *datahsh, char *input)
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
		datahsh->args = split_line(datahsh->input);
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

/**
 * char_swap - swap & and | for non printed chars
 * @input: input string
 * @bool: either 1 or 0.
 *
 * Return: swapped input string
 */

char *char_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command line to the lists
 * @h_s: head of separator list
 * @h_l: head of command line list
 * @input: input string
 *
 * Return: void.
 */

void add_nodes(sep_list **h_s, line_list **h_l, char *input)
{
	int i;
	char *line;

	input = char_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(h_s, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(h_s, input[i]);
			i++;
		}
	}
	line = _strtok(input, ";|&");
	do {
		line = char_swap(line, 1);
		add_line_node_end(h_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * next_command - moves to the next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @datahsh: data
 *
 * Return: void.
 */

void next_command(sep_list **list_s, line_list **list_l, info_shell *datahsh)
{
	int loop;
	sep_list *ls_s;
	line_list *ls_l;

	loop = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop)
	{
		if (datahsh->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop = 0;
			if (ls_s->separator == '|')
			{
				ls_l = ls_l->next;
				ls_s = ls_s->next;
			}
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop)
			ls_s = ls_s->next;
	}
	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_line - tokenizes the user input string
 * @input: input string
 *
 * Return: array of tokenized input
 */

char **split_line(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
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
