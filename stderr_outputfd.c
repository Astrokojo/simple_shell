#include "header.h"


/**
 * _puttchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1, error -1
 */
int _puttchar(char c)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putts - prints a string
 * @str: string
 *
 */
void _putts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_puttchar(str[i]);
		i++;
	}
}

/**
 * _putcharfd - writes the character c to given fd
 * @c: The character to print
 * @fd: file descriptor
 * Return: On success 1, error -1
 */
int _putcharfd(char c, int fd)
{
	static int i;
	static char buf[BUF_SIZE];

	if (c == BUF_FLUSH || i >= BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - prints a string
 * @str: string
 * @fd: output, file descriptor
 *
 * Return: the number of chars
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putcharfd(*str++, fd);
	}
	return (i);
}
