#include "header.h"

/**
 * _alias -  alias cmd
 * @shell_info: input
 *  Return: Always 0
 */
int _alias(shell_info_t *shell_info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (shell_info->argc == 1)
	{
		node = shell_info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell_info->argv[i]; i++)
	{
		ptr = _strchr(shell_info->argv[i], '=');
		if (ptr)
			set_alias(shell_info, shell_info->argv[i]);
		else
			print_alias(node_starts_with(shell_info->alias, shell_info->argv[i], '='));
	}

	return (0);
}
