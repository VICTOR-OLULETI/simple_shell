#include "main.h"

/**
 * _memcpy - copies information to a new pointer
 * @newptr: new pointer
 * @ptr: source pointer
 * @size: size of new pointer
 *
 * Return: void.
 */

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int j;

	for (j =  0; j < size; j++)
		char_newptr[j] = char_ptr[j];
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the previously allocated memory
 * @old_size: size of previously allocated memory
 * @new_size: new size of newly allocated memory bloc
 *
 * Return: pointer to new memory or NULL if malloc fails
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - reallocates a block of memory of a double ptr
 * @ptr: double pointer to previously allocated memory.
 * @old_size: size of the previously allocated memory.
 * @new_size: size of newly allocated memory
 *
 * Return: pointer to new block of memory or NULL if failure
 */

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];
	free(ptr);

	return (newptr);
}
