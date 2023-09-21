#include "header.h"

/**
 * get_environ - function prints env string arrays
 * @shell_info: input value
 * Return: Always 0
 */
char **get_environ(shell_info_t *shell_info)
{
	if (!shell_info->environ || shell_info->env_changed)
	{
		shell_info->environ = list_to_strings(shell_info->env);
		shell_info->env_changed = 0;
	}

	return (shell_info->environ);
}

/**
 *_setenv_struct - sets a new environment variable
 * @shell_info: ditto
 *Return: Always 0
 */
int _setenv_struct(shell_info_t *shell_info)
{
	if (shell_info->argc != 3)
	{
		_putts("incorrect num of args\n");
		return (1);
	}

	if (_setenv(shell_info, shell_info->argv[1], shell_info->argv[2]))
		return (0);
	return (1);
}

/**
 *_unsetenv_struct - deselects an environment variable
 * @shell_info: input value
 *Return: 1 on delete, 0 otherwise
 **/
int _unsetenv_struct(shell_info_t *shell_info)
{
	int i;

	if (shell_info->argc == 1)
	{
		_putts("Too few args.\n");
		return (1);
	}
	for (i = 1; i <= shell_info->argc; i++)
		_unsetenv(shell_info, shell_info->argv[i]);

	return (0);
}

