#include "header.h"

/**
 * main - Entry into a simple shell program
 *
 *
 * Return: 0
 */
int main(void)
{
	char *buf = NULL;
	int user_input;
	char **argv = NULL;
	int argc = 0;

	while (1)
	{
		shell_prompt();

		user_input = get_input(&buf);

		argv = malloc(sizeof(char *) * (user_input + 1));

		if (argv == NULL)
		{
			perror("malloc");
			exit(1);
		}

		cmd_token(buf, argv);

		cmd_exe(argv);

		argc = 0;
		free(argv);
	}
	free(buf);

	return (0);
}
