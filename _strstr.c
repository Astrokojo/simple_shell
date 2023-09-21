#include "header.h"
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
