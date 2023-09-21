#include "header.h"

/**
 * remove_comment - function that handles #
 * @buf: str buffer
 *
 * Return: Always 0;
 */
void remove_comment(char *buf)
{
	int hash;

	for (hash = 0; buf[hash] != '\0'; hash++)
		if (buf[hash] == '#' && (!hash || buf[hash - 1] == ' '))
		{
			buf[hash] = '\0';
				break;
		}
}
