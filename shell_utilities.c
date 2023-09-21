#include "header.h"
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
