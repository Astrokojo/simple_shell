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
