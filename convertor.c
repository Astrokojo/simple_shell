#include "header.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 success, otherwise -1 on error
 */
int _erratoi(char *str)
{
	int i = 0;
	int result = 0;
	int sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= 9)
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (sign == -1 ? INT_MIN : INT_MAX);
		}
		else
			return (-1);
	}
	return (result * sign);
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

	if (current == 0)
	{
		__putchar('0');
		count++;
	}

	else
	{
		for (i = 1000000000; i > 0; i /= 10)
		{
			if (current / i > 0 || count > 0)
			{
				__putchar('0' + current / i);
				count++;
			}

current %= i;
		}
	}
	return (count);
}

/**
 * convert_number - convert long int number into string
 * @num: numbere
 * @base: base
 * @flags: argv
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;
	static char *array;

	if (!(flags & TO_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & TO_LWRCASE ? "0123456789abcdef" : "0123456789ABCDEF";

	ptr = &buffer[sizeof(buffer) - 1];
	*ptr = '\0';

	while (n != 0)
	{
		*--ptr = array[n % base];
		n /= base;
	}

	if (sign)
		*--ptr = sign;

	return (ptr);
}
