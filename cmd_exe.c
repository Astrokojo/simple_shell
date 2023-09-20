#include "header.h"
/**
 * cmd_exe - execute the shell commands
 *@argv: arguments
 *
 */
void cmd_exe(char *argv[])
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("Pid didnt fork");
		exit(1);
	}
	else if (pid == 0)
	{
		int exe = execve(argv[0], argv, NULL);

		if (exe == -1)
			perror("Execve failed");
	}
	else
		wait(&status);
}
