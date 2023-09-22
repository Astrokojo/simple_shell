#include "header.h"

/**
 * shell_hist - prints the history list
 * @sh: input value
 *  Return: Always 0
 */
int shell_hist(shell_t *sh)
{
	print_list(sh->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @sh: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(shell_t *sh, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_node(&(sh->alias),
		get_node_index(sh->alias, node_starts_with(sh->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @sh: input
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(shell_t *sh, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(sh, str));

	unset_alias(sh, str);
	return (add_node_end(&(sh->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - replica of alias embedded_cmd
 * @sh: ...
 *  Return: Always 0
 */
int _alias(shell_t *sh)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (sh->argc == 1)
	{
		node = sh->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; sh->argv[i]; i++)
	{
		p = _strchr(sh->argv[i], '=');
		if (p)
			set_alias(sh, sh->argv[i]);
		else
			print_alias(node_starts_with(sh->alias, sh->argv[i], '='));
	}

	return (0);
}
