#include "header.h"
/**
 *sigintHandler - interrupts the ctrl-C function
 *@sig_num: the signal number
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
