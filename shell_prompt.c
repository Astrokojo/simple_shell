#include "header.h"
void shell_prompt(void)
{
	char *prompt = "$ ";
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, prompt, 2);
}
