#include "header.h"

/**
 * interactive - checks if terminal is in interactive mode
 * @shell_info: struct
 *Return: 1 if interactive mode, 0 otherwise
 */
int interactive(shell_info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->readfd <= 2);
}

