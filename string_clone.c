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

/**
 * _strcpy - copies a string from src to dest
 * @src: the string source
 * @dest: string destination
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}

/**
 *_strncpy - copies a string
 *@src: the source string
 *@dest: the destination string
 *@num: num of bytes to copy
 *Return: returns pointer to resulting string dest
 */
char *_strncpy(char *dest, char *src, int num)
{
	int i;

	for (i = 0; src[i] && i < num; i++)
		dest[i] = src[i];
	for ( ; i < num; i++)
		dest[i] = '\0';
	return (dest);
}
