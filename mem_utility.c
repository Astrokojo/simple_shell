#include "header.h"
/**
 *_memset - fills memory with a constant byte
 *@area: the pointer to the memory area
 *@input: input
 *@num: num
 *Return: area value
 */
char *_memset(char *area, char input, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		area[i] = input;
	return (area);
}

/**
 *_realloc - reallocates a block of memory
 *@ptr: pointer to previous malloc
 *@old_size: initial size
 *@new_size: current size
 *
 *Return: pointer to prev memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *c;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	c = malloc(new_size);
	if (!c)
	return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	c[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (c);
}
	while (*str_arr)
		free(*str_arr++);
	free(current_str);
}
