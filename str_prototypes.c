#include "header.h"

/**
 * _strlen - finds the length of a string
 * @str: param for string
 * Return: 0 Success
 */
int _strlen(char *str)
{
	int i = 0;

	while (str[i])
		++i;

	return (i);
}

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
 *_strchr - locates a character in a string
 *@str: the string to be parsed
 *@c: the character to look for
 *Return: (str) a pointer to the memory area str
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);
		str++;
	}

	return (NULL);
}
