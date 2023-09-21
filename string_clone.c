#include "header.h"
/**
 *_strdup - duplicates a string
 *@str: a string parameter
 *
 *Return: NULL or a pointer
 */
char *_strdup(const char *str)
{
	char *dup;
	int length = 0;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	dup = malloc(sizeof(char) * (length + 1));

	if (!dup)
		return (NULL);

	for (length++; length--;)
		dup[length] = *--str;

	return (dup);
}
