#include "header.h"

/**
 * interactive - displays true if shell is interactive mode
 * @sh: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(shell_t *sh)
{
	return (isatty(STDIN_FILENO) && sh->readfd <= 2);
}

/**
 * _delim - checks if character is a delimiter
 * @c: the char to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int _delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}
