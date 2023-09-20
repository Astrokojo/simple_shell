#include "header.h"
/**
 * shell_prompt - creates a prompt like a shell terminal
 */
void shell_prompt(void)
{
	char *prompt = "$ ";

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);
}
