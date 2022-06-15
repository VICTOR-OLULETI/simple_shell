#include "main.h"

/**
 * replace_input - replaces variable wih string
 * @h: head of linked list
 * @input: input string
 * @n_input: new input string
 * @n_len: new length
 * Return: new input string
 */

char *replace_input(r_var **h, char *input, char *n_input, int n_len)
{
	r_var *index;
	int i, j, k;

	index = *h;
	for (i = j = 0; i < n_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				n_input[i] = input[i];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					n_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			n_input[i] = input[j];
			j++;
		}
	}
	return (n_input);
}
