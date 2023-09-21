#include "header.h"

/**
 * print_shell - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int print_shell(shell_info_t *info, char **av)
{
	ssize_t sh = 0;
	int builtin_cmd = 0;

	while (sh != -1 && builtin_cmd != -2)
	{
		clear_shell_info(info);
		if (interactive(info))
			_puts("$ ");
		_puttchar(BUFF_FLUSH);
		sh = get_input(info);
		if (sh != -1)
		{
			set_shell_info(info, av);
			builtin_cmd = find_builtin(info);
			if (builtin_cmd == -1)
				cmd_path(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_shell_info(info, 0);
	}
	write_hist(info);
	free_shell_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_cmd == -2)
	{
		if (info->errors == -1)
			exit(info->status);
		exit(info->errors);
	}
	return (builtin_cmd);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int find_builtin(shell_info_t *info)
{
	int i, builtin_sig = -1;
	builtin_tbl table[] = {
		{"alias", _alias},
		{"cd", _cd_},
		{"env", _env_},
		{"exit", _exit_},
		{"help", _help_},
		{"history", print_sh_hist},
		{"setenv", _setenv_},
		{"unsetenv", _unsetenv_},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
		if (_strcmp(info->argv[0], table[i].type) == 0)
		{
			info->counter++;
			builtin_sig = table[i].func(info);
			break;
		}
	return (builtin_sig);
}

/**
 * cmd_path - searches for a command in PATH
 * @info: the parameter
 * Return: the info struct
 */
void cmd_path(shell_info_t *info)
{
	char *path = NULL;
	int element, key;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->counter++;
		info->linecount_flag = 0;
	}
	for (element = 0, key = 0; info->arg[element]; element++)
		if (!chk_delim(info->arg[element], " \t\n"))
			key++;
	if (!key)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_pid(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && prints_cmd(info, info->argv[0]))
			fork_pid(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_pid - forks a process to run new commands
 * @info: the parameter
 *
 * Return: void
 */
void fork_pid(shell_info_t *info)
{
	pid_t _pid;

	_pid = fork();
	if (_pid == -1)
	{
		perror("Error: Failed to fork");
		return;
	}
	if (_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_shell_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
