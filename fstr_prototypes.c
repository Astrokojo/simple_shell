#include "header.h"
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
