#include "header.h"

/**
 * set_alias - sets alias to al_str string
 * @shell_info: input
 * @str: the string alias
 *
 *
 * Return: Always 0 Success, 1 Error
 */
int set_alias(shell_info_t *shell_info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(shell_info, str));

	unset_alias(shell_info, str);
	return (add_node_end(&(shell_info->alias), str, 0) == NULL);
}


/**
 * unset_alias - unsets an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 Success, 1 Error
 */
int unset_alias(shell_info_t *info, char *str)
{
	char *ptr;
	char c;
	int ret;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = del_at_index(&(info->alias),
			at_index(info->alias,
				node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (ret);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL;
	char *al_str = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (al_str = node->str; al_str <= ptr; al_str++)
			_putchar(*al_str);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

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

