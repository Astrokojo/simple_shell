#include "header.h"
/**
 *print_error - prints an error message
 *@shell_info: ...
 *@errtype: string that shows error type
 *Return: 0 success, otherwise -1 on error
 */
void print_error(shell_info_t *shell_info, char *errtype)
{
	_putts(shell_info->fname);
	_putts(": ");
	print_d(shell_info->counter, STDERR_FILENO);
	_putts(": ");
	_putts(shell_info->argv[0]);
	_putts(": ");
	_putts(errtype);
}
