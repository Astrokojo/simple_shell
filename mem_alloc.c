#include "header.h"

/**
 **_memset - fills memory with a constant byte
 *@c: the pointer to the memory area
 *@b: input
 *@n: num
 *Return: s value
 */
char *_memset(char *c, char b, unsigned int n)
{
	unsigned int u;

	for (u = 0; u < n; u++)
		c[u] = b;
	return (c);
}

/**
 *free_ptr: frees a pointer
 *@ptr: pointer
 *
 * Return: 1 Success, 0 Else
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
		return (0);
}
/**
 * free_str_arr - frees a string of strings
 * @pp: strings to free
 */
void free_str_arr(char **pp)
{
	char **f = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(f);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc
 * @old_size: initial size
 * @new_size: current size
 *
 * Return: pointer to prev memory
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
