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

/**
 * _strstr - locates a substring
 * @haystack: stack to search through
 * @needle: the substring to match
 *
 * Return: address of next char of haystack or NULL
 */
char *_strstr(const char *haystack, const  char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}
