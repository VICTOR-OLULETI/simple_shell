#include "main.h"

/**
 * env_check - checks if the input string ia an env variable
 * @h: head of linked list
 * @input: input string
 * @data: data/ information
 *
 * Return: void.
 */

void env_check(r_var **h, char *input, info_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_rvar_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}
			if (input[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t'
		|| input[j] == ';' || input[j] == '\n')
			break;
	}
	add_rvar_node(h, j, NULL, 0);
}

/**
 * var_check - check for $$ or $ in the typed variable
 * @h: head of the linked list
 * @input: input string
 * @st: last state of the shell
 * @data: data
 *
 * Return: void.
 */
int var_check(r_var **h, char *input, char *st, info_shell *data)
{
	int i;
	int lst;
	int lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
				add_rvar_node(h, 2, st, lst), i++;
			else if (input[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (input[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (input[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				env_check(h, input + i, data);
		}
	}
	return (i);
}

/**
 * replace_input - replaces string into variables
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string
 * @nlen: new length
 *
 * Return: replaced string
 */
char *replace_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (i = j = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replace_var - set of function to replace string into vars
 * @input: input string
 * @datahsh: data structure
 *
 * Return: replaced string
 */
char *replace_var(char *input, info_shell *datahsh)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = _itoa(datahsh->status);
	head = NULL;

	olen = var_check(&head, input, status, datahsh);
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	indx = head;
	nlen = 0;
	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}
	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';
	new_input = replace_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
