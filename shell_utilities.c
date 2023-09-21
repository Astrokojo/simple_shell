#include "header.h"
/**
 *remove_comments -handles the hashtag(#) in comments
 *@buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int comment;

	for (comment = 0; buf[comment] != '\0'; comment++)
		if (buf[comment] == '#' && (!comment || buf[comment - 1] == ' '))
		{
			buf[comment] = '\0';
			break;
		}
}

/**
 * shell_hist - print the shell history
 * @shell_info: inpit
 * Return: 0 Success
 */
int shell_hist(shell_info_t *shell_info)
{
	print_list(shell_info->history);
	return (0);
}