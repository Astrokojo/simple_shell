#include "header.h"

/**
 *_puts - print a string then a '\n' to stdout
 *@str: the string to be printed
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i++]);
	}
	_putchar('\n');
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		(write(1, buf, i));
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
