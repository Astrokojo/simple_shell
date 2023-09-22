#include "header.h"

/**
 * clear_sh - restarts shell_t struct
 * @sh: struct address
 */
void clear_sh(shell_t *sh)
{
	sh->arg = NULL;
	sh->argv = NULL;
	sh->path = NULL;
	sh->argc = 0;
}

/**
 * set_sh - initializes shell_t struct
 * @sh: struct address
 * @av: argument vector
 */
void set_sh(shell_t *sh, char **av)
{
	int s = 0;

	sh->fname = av[0];
	if (sh->arg)
	{
		sh->argv = strtow(sh->arg, " \t");
		if (!sh->argv)
		{

			sh->argv = malloc(sizeof(char *) * 2);
			if (sh->argv)
			{
				sh->argv[0] = _strdup(sh->arg);
				sh->argv[1] = NULL;
			}
		}
		for (s = 0; sh->argv && sh->argv[s]; s++)
			;
		sh->argc = s;

		change_alias(sh);
		change_vars(sh);
	}
}

/**
 * free_sh - frees the shell_t struct
 * @sh: struct address
 * @all: ...
 */
void free_sh(shell_t *sh, int all)
{
	free_str_arr(sh->argv);
	sh->argv = NULL;
	sh->path = NULL;
	if (all)
	{
		if (!sh->cmd_buff)
			free(sh->arg);
		if (sh->env)
			free_list(&(sh->env));
		if (sh->history)
			free_list(&(sh->history));
		if (sh->alias)
			free_list(&(sh->alias));
		free_str_arr(sh->environ);
			sh->environ = NULL;
		free_ptr((void **)sh->cmd_buff);
		if (sh->readfd > 2)
			close(sh->readfd);
		_putchar(BUFF_FLUSH);
	}
}
