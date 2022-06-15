#include "main.h"

/**
 * add_nodes - add separator and command line to list
 * @h1: head of separator list
 * @h2: head of command line list
 * @input: input string
 * Return: void.
 */

void add_nodes(sep_list **h1, line_list **h2, char *input)
{
	int j;
	char *token;

	input = char_swap(input, 0);
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ';')
			add_sep_node_end(h1, input[j]);
		if (input[j] == '|' || input[j] == '&')
		{
			add_sep_node_end(h1, input[j]);
			j++;
		}
	}
	token = _strtok(input, ";|&");
	do {
		token = char_swap(token, 1);
		add_line_node_end(h2, token);
		token = _strtok(NULL, ";|&");
	} while (token != NULL);
}

/**
 * next_command - moves to the next command line stored
 * @list_s: separator lnked list
 * @list_l: command line linked list
 * @datahsh: data
 * REturn: void.
 */
void next_command(sep_list **list_s, line_list **list_l, info_shell *datahsh)
{
	int loop;
	sep_list *lt_s;
	line_list *lt_l;

	loop = 1;
	lt_s = *list_s;
	lt_l = *list_l;

	while (lt_s != NULL && loop)
	{
		if (datahsh->status == 0)
		{
			if (lt_s->separator == '&' || lt_s->separator == ';')
				loop = 0;
			if (lt_s->separator == '|')
				lt_l = lt_l->next, lt_s = lt_s->next;
		}
		else
		{
			if (lt_s->separator == '|' || lt_s->separator == ';')
				loop = 0;
			if (lt_s->separator == '&')
				lt_l = lt_l->next, lt_s = lt_s->next;
		}
		if (lt_s != NULL && !loop)
			lt_s = lt_s->next;
	}

	*list_s = lt_s;
	*list_l = lt_l;
}
