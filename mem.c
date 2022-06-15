#include "main.h"

/**
 * _memcpy - copies a block of memory
 * @newptr: new pointer
 * @ptr: old pointer to block of memory
 * @size: size of ptr
 *
 * Return: void
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *) ptr;
	char *char_newptr = (char *) newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: new pointer
 * @old_size: size of old block of memory
 * @new_size: new size to be realloated
 *
 * Return: void.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(sizeof(char) * new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(sizeof(char) * new_size);
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
 * _reallocdp - reallocated a double pointer
 * @ptr: new double pointer
 * @old_size: size of previous block of memory
 * @new_size: size of new block of memory
 *
 * Return: pointer to new allocated memory.
 */

char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));
	if (new_size == old_size)
		return (newptr = malloc(sizeof(char *) * new_size));
	if (newptr == NULL)
		return (NULL);
	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];
	free(ptr);
	return (newptr);
}
