#include "header.h"

/**
 *shell_loop - main shell loop
 *@shell_info: shell_info struct
 *@av: the argv form main()
 *
 *Return: 0 on success, 1 on error, or error code
 */
int shell_loop(shell_info_t *shell_info, char **av)
{
	ssize_t sh = 0;
	int cmd_code = 0;

	while (sh != -1 && cmd_code != -2)
	{
		clear_shell_info(shell_info);

		if (interactive(shell_info))
			_puts("$ ");
		_puttchar(BUF_FLUSH);
		sh = get_input(shell_info);
		if (sh != -1)
		{
			set_shell_info(shell_info, av);
			cmd_code = find_cmd(shell_info);
			if (cmd_code == -1)
				parse_cmd(shell_info);
		}
		else if (interactive(shell_info))
			_putchar('\n');
		free_shell_info(shell_info, 0);
	}
	write_hist(shell_info);

	free_shell_info(shell_info, 1);

	if (!interactive(shell_info) && shell_info->status)
		exit(shell_info->status);

	if (cmd_code == -2)
	{
		if (shell_info->errors == -1)
			exit(shell_info->status);

		exit(shell_info->errors);
	}
	return (cmd_code);
}
/**
 * find_cmd - finds a cmd
 * @shell_info: shell_info struct
 *
 * Return: -1 if cmd not found,
 * 0 if cmd executed successfully,
 * 1 if cmd found but not successful,
 * -2 if cmd signals exit()
 */
int find_cmd(shell_info_t *shell_info)
{
	int index, cmd_code = -1;
	cmd_tab cmdtbl[] = {
		{"alias", _alias},
		{"cd", _chdir},
		{"env", current_env},
		{"exit", _exit_sh},
		{"help", _help_},
		{"history", shell_hist},
		{"setenv", _setenv_struct},
		{"unsetenv", _unsetenv_struct},
		{NULL, NULL}
	};

	for (index = 0; cmdtbl[index].type; index++)
		if (_strcmp(shell_info->argv[0], cmdtbl[index].type) == 0)
		{
			shell_info->counter++;
			cmd_code = cmdtbl[index].func(shell_info);
			break;
		}
	return (cmd_code);
}

/**
 * parse_cmd - finds a cmd from a PATH
 * @shell_info: shell_info struct
 *
 */
void parse_cmd(shell_info_t *shell_info)
{
	char *path = NULL;
	int elem, key;

	shell_info->path = shell_info->argv[0];
	if (shell_info->linecount_flag == 1)
	{
		shell_info->counter++;
		shell_info->linecount_flag = 0;
	}
	for (elem = 0, key = 0; shell_info->arg[elem]; elem++)
		if (!chk_delim(shell_info->arg[elem], " \t\n"))
			key++;
	if (!key)
		return;

	path = find_path(shell_info,
			_getenv(shell_info, "PATH="),
			shell_info->argv[0]);
	if (path)
	{
		shell_info->path = path;
		child_pid(shell_info);
	}
	else
	{
		if ((interactive(shell_info) || _getenv(shell_info, "PATH=")
			|| shell_info->argv[0][0] == '/') && prints_cmd(shell_info,
				shell_info->argv[0]))
			child_pid(shell_info);
		else if (*(shell_info->arg) != '\n')
		{
			shell_info->status = 127;
			print_error(shell_info, "not found\n");
		}
	}
}
