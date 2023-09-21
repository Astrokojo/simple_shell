#include "header.h"
/**
 *chk_delim - checks if character is a delimeter
 *@c: the char to check
 *@delim: the delimeter string
 *Return: 1 if true, 0 if false
 */
int chk_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * **_strtok - splits a string into words
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *str, char *d)
{
	int x, y = 0;
	int a, b, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!chk_delim(str[x], d) && (chk_delim(str[x + 1], d) || !str[x + 1]))
			words++;

	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < words; y++)
	{
		while (chk_delim(str[x], d))
			x++;
		a = 0;
		while (!chk_delim(str[x + a], d) && str[x + a])
			a++;
		s[y] = malloc((a + 1) * sizeof(char));
		if (!s[y])
		{
			for (a = 0; a < y; a++)
				free(s[a]);
			free(s);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			s[y][b] = str[x++];
		s[y][b] = 0;
	}
	s[y] = NULL;
	return (s);
}
