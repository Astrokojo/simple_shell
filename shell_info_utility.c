#include "header.h"

/**
 * clear_shell_info - restarts shell_info_t struct
 * @shell_info: struct address
 */
void clear_shell_info(shell_info_t *shell_info)
{
	shell_info->arg = NULL;
	shell_info->argv = NULL;
	shell_info->path = NULL;
	shell_info->argc = 0;
}

/**
 * set_shell_info - initializes shell_info_t struct
 * @shell_info: struct address
 * @av: argument vector
 */
void set_shell_info(shell_info_t *shell_info, char **av)
{
	int s = 0;

	shell_info->fname = av[0];
	if (shell_info->arg)
	{
		shell_info->argv = _strtok(shell_info->arg, " \t");
		if (!shell_info->argv)
		{

			shell_info->argv = malloc(sizeof(char *) * 2);
			if (shell_info->argv)
			{
				shell_info->argv[0] = _strdup(shell_info->arg);
				shell_info->argv[1] = NULL;
			}
		}
		for (s = 0; shell_info->argv && shell_info->argv[s]; s++)
			;
		shell_info->argc = s;

		update_alias(shell_info);
		update_vars(shell_info);
	}
}

/**
 * free_shell_info - frees the shell_info_t struct
 * @shell_info: struct address
 * @all: ...
 */
void free_shell_info(shell_info_t *shell_info, int all)
{
	free_str_arr(shell_info->argv);
	shell_info->argv = NULL;
	shell_info->path = NULL;
	if (all)
	{
		if (!shell_info->cmd_buff)
			free(shell_info->arg);
		if (shell_info->env)
			free_list(&(shell_info->env));
		if (shell_info->history)
			free_list(&(shell_info->history));
		if (shell_info->alias)
			free_list(&(shell_info->alias));
		free_str_arr(shell_info->environ);
			shell_info->environ = NULL;
		freeptr((void **)shell_info->cmd_buff);
		if (shell_info->readfd > 2)
			close(shell_info->readfd);
		_putchar(BUFF_FLUSH);
	}
}
