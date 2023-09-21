#include "header.h"

/**
 * print_sh_hist - prints the history list
 * @info: input value
 *  Return: Always 0
 */
int print_sh_hist(shell_info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from string
 * @info: param struct
 * @str: the alias for a string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(shell_info_t *info, char *str)
{
	char *ptr, c;
	int unset;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	unset = del_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (unset);
}

/**
 * set_alias - sets alias to string
 * @info: input
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(shell_info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *i = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (i = node->str; i <= ptr; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - alias built-in cmd
 * @info: the param and struct
 *  Return: Always 0
 */
int _alias(shell_info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
