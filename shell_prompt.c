#include "header.h"

/**
 * print_shell - main shell loop
 * @sh: struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int print_shell(shell_t *sh, char **av)
{
	ssize_t sz = 0;
	int embedded_cmd_val = 0;

	while (sz != -1 && embedded_cmd_val != -2)
	{
		clear_sh(sh);
		if (interactive(sh))
			_puts("$ ");
		_puttchar(BUFF_FLUSH);
		sz = get_input(sh);
		if (sz != -1)
		{
			set_sh(sh, av);
			embedded_cmd_val = find_embedded_cmd(sh);
			if (embedded_cmd_val == -1)
				parse_cmd(sh);
		}
		else if (interactive(sh))
			_putchar('\n');
		free_sh(sh, 0);
	}
	write_hist(sh);
	free_sh(sh, 1);
	if (!interactive(sh) && sh->status)
		exit(sh->status);
	if (embedded_cmd_val == -2)
	{
		if (sh->errors == -1)
			exit(sh->status);
		exit(sh->errors);
	}
	return (embedded_cmd_val);
}

/**
 * find_embedded_cmd - finds an embeddedcomnd
 * @sh: struct
 *
 * Return: -1 if embedded_cmd not found,
 * 0 if embedded_cmd executed successfully,
 * 1 if embedded_cmd found but not successful,
 * 2 if embedded_cmd signals exit()
 */
int find_embedded_cmd(shell_t *sh)
{
	int idx, built_in_ret = -1;
	embedded_cmd_tab embedded_cmdtbl[] = {
		{"exit", _exit_},
		{"env", _env_},
		{"help", _help_},
		{"history", shell_hist},
		{"setenv", _setenv_},
		{"unsetenv", _unsetenv_},
		{"cd", _cd_},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (idx = 0; embedded_cmdtbl[idx].type; idx++)
		if (_strcmp(sh->argv[0], embedded_cmdtbl[idx].type) == 0)
		{
			sh->errcounter++;
			built_in_ret = embedded_cmdtbl[idx].func(sh);
			break;
		}
	return (built_in_ret);
}

/**
 * parse_cmd - searches for a command in PATH
 * @sh: struct
 *
 */
void parse_cmd(shell_t *sh)
{
	char *path = NULL;
	int element, key;

	sh->path = sh->argv[0];
	if (sh->linecount_flag == 1)
	{
		sh->errcounter++;
		sh->linecount_flag = 0;
	}
	for (element = 0, key = 0; sh->arg[element]; element++)
		if (!_delim(sh->arg[element], " \t\n"))
			key++;
	if (!key)
		return;

	path = find_path(sh, _getenv(sh, "PATH="), sh->argv[0]);
	if (path)
	{
		sh->path = path;
		fork_pid(sh);
	}
	else
	{
		if ((interactive(sh) || _getenv(sh, "PATH=")
			|| sh->argv[0][0] == '/') && prints_cmd(sh, sh->argv[0]))
			fork_pid(sh);
		else if (*(sh->arg) != '\n')
		{
			sh->status = 127;
			print_err(sh, "not found\n");
		}
	}
}

/**
 * fork_pid - forks a an exec thread to run cmd
 * @sh: struct
 *
 * Return: void
 */
void fork_pid(shell_t *sh)
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
		if (execve(sh->path, sh->argv, get_environ(sh)) == -1)
		{
			free_sh(sh, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(sh->status));
		if (WIFEXITED(sh->status))
		{
			sh->status = WEXITSTATUS(sh->status);
			if (sh->status == 126)
				print_err(sh, "Permission denied\n");
		}
	}
}
