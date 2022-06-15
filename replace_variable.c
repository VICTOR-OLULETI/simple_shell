#include "main.h"

/**
 * replace_var - replace string into variables
 * @input: input string
 * @datahsh: data
 * Return: replaced string into variable
 */
char *replace_var(char *input, info_shell *datahsh)
{
	r_var *h, *index;
	char *status, *n_input;
	int old_len, new_len;

	status = _itoa(datahsh->status);
	h = NULL;
	old_len = var_check(&h, input, status, datahsh);

	if (h == NULL)
	{
		free(status);
		return (input);
	}
	index = h;
	new_len = 0;
	while (index != NULL)
	{
		new_len += (index->len_val - index->len_var);
		index = index->next;
	}
	new_len += old_len;
	n_input = malloc(sizeof(char) * (new_len + 1));
	n_input[new_len] = '\0';

	n_input = replace_input(&h, input, n_input, new_len);

	free(input);
	free(status);
	free_rvar_list(&h);
	return (n_input);
}
