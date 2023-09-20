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
	char *token;
	const char *delim = " \n";
	char **argv = NULL;
	int argc = 0;
	pid_t pid;
	int status;

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

		token = strtok(buf, delim);

		while (token)
		{
			argv[argc] = strdup(token);
			token = strtok(NULL, delim);
			argc++;
		}

		argv[argc] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("pid did not fork");
			exit(1);
		}

		else if (pid == 0)
		{
			int exe = execve(argv[0], argv, NULL);

			if (exe == -1)
			{
				perror("Error: Execve failed");
				exit(1);
			}
		}

		else
			wait(NULL);

		argc = 0;
		free(argv);
	}
	free(buf);

	return (0);
}
