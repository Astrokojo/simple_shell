#include "header.h"
/**
 *chk_delim - checks if character is counter1 delimeter
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
 * **_strtok - splits counter1 string into counter3
 * @str: the input string
 * @d: the delimeter string
 * Return: counter1 pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *str, char *d)
{
	int i, j = 0;
	int counter1, counter2, counter3 = 0;
	char **ptr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!chk_delim(str[i], d) && (chk_delim(str[i + 1], d) || !str[i + 1]))
			counter3++;

	if (counter3 == 0)
		return (NULL);
	ptr = malloc((1 + counter3) * sizeof(char *));
	if (!ptr)
		return (NULL);
	for (i = 0, j = 0; j < counter3; j++)
	{
		while (chk_delim(str[i], d))
			i++;
		counter1 = 0;
		while (!chk_delim(str[i + counter1], d) && str[i + counter1])
			counter1++;
		ptr[j] = malloc((counter1 + 1) * sizeof(char));
		if (!ptr[j])
		{
			for (counter1 = 0; counter1 < j; counter1++)
				free(ptr[counter1]);
			free(ptr);
			return (NULL);
		}
		for (counter2 = 0; counter2 < counter1; counter2++)
			ptr[j][counter2] = str[i++];
		ptr[j][counter2] = 0;
	}
	ptr[j] = NULL;
	return (ptr);
}
