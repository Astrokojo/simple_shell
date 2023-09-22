#include "header.h"

/**
 * comment_handler - function handles the #
 * @buf: address containing comment
 *
 * Return: Always 0;
 */
void comment_handler(char *buf)
{
	int comment;

	for (comment = 0; buf[comment] != '\0'; comment++)
		if (buf[comment] == '#' && (!comment || buf[comment - 1] == ' '))
		{
			buf[comment] = '\0';
			break;
		}
}
