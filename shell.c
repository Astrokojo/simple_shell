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
	size_t n = 0;
	ssize_t user_input;
	char *token;
	const char *delim = " \n";
	char **argv = NULL;
	int argc = 0;
	pid_t pid;
	int status;

	while (1)
	{
		printf("$ ");

		user_input = getline(&buf, &n, stdin);

		if (user_input == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}

			else
			{
				perror("getline");
				free(buf);
				exit(1);
			}
		}

		argv = malloc((size_t)(user_input + 1) * sizeof(*argv));

		if (argv == NULL)
		{
			perror("malloc");
			free(buf);
			exit(1);
		}

		token = strtok(buf, delim);

		while (token)
		{
			argv[argc++] = strdup(token);
			token = strtok(NULL, delim);
		}

		argv[argc] = NULL;

		pid = fork();
		
		if (pid == -1)
		{
			perror("pid did not fork");
			free(buf);
			for (int i = 0; i < argc; i++)
				free(argv[i]);
			free(argv);
			exit(1);
		}

		else if (pid == 0)
		{
			int exe = execve(argv[0], argv, NULL);

			if (exe == -1)
			{
				perror("Error: Execve failed");
				free(buf);
				for (int i = 0; i < argc; i++)
					free(argv[i]);
				free(argv);
				exit(1);
			}
		}

		else
		{
			wait(NULL);
			
			for (int i = 0; i < argc; i++)
				free(argv[i]);
			free(argv);
			free(buf);
		}
	}
	return (0);
}
