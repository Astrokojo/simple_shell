#include "header.h"

/**
 * set_alias - sets alias to a string
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
	char *a = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 *replace_alias - replaces an aliases
 *@shell_info: ...
 *
 *Return: 1 Success, Else 0
 */
int replace_alias(shell_info_t *shell_info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(shell_info->alias, shell_info->argv[0], '=');

		if (!node)
			return (0);
		free(shell_info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		shell_info->argv[0] = ptr;
							}
		return (1);
}
