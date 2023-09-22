#include "header.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 success, otherwise -1 on error
 */
int _atoi(char *s)
{
	int i = 0;
	int result = 0;
	int sign = 1;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (sign == -1 ? INT_MIN : INT_MAX);
		}
		else
			return (-1);
	}
	return (result * sign);
}

/**
 * print_err - prints an error message
 * @sh: ...
 * @estr: string that shows error type
 * Return: 0 success, otherwise -1 on error
 */
void print_err(shell_t *sh, char *estr)
{
	_putts(sh->fname);
	_putts(": ");
	print_d(sh->errcounter, STDERR_FILENO);
	_putts(": ");
	_putts(sh->argv[0]);
	_putts(": ");
	_putts(estr);
}

/**
 * print_d - function prints an int in base 10
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _puttchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar(48 + current / i);
			count++;
		}
		current %= i;
	}
	__putchar(48 + current);
	count++;

	return (count);
}

/**
 * convert_number - function is a iota replica
 * @num: number value
 * @base: input
 * @flags: arg value
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & 2) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
