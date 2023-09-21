#include "header.h"

/**
 * _strcat - concatenates two strings
 * @dest: first string
 * @src: second str
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	char *concat_str = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (concat_str);
}


/**
 *_strncat - concats two srings
 *@dest: the dest string
 *@src: the source string
 *@num: the amount of bytes to concat
 *
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int num)
{
	int i, j;

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j] && j < num; j++)
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: the first str
 * @s2: the second str
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}
