#include "header.h"
/**
 *child_pid - creates a child process
 *@shell_info: shell_info struct
 *
 *Return: void
 */
void child_pid(shell_info_t *shell_info)
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return;
	}

	if (pid == 0)
	{
		if (execve(shell_info->path,
					shell_info->argv,
					get_environ(shell_info)) == -1)
		{
			free_shell_info(shell_info, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}

	else
	{
		wait(&(shell_info->status));
		if (WIFEXITED(shell_info->status))
		{
			shell_info->status = WEXITSTATUS(shell_info->status);
			if (shell_info->status == 126)
				print_error(shell_info, "Not allowed \n");
		}
	}
}
