#include "header.h"

/**
 * current_env - prints the current environment
 * @shell_info: inot
 * Return: Always 0
 */
int current_env(shell_info_t *shell_info)
{
	print_list_str(shell_info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @shell_info: inpyt
 * @name: ennviron name
 *
 * Return: the value
 */
char *_getenv(shell_info_t *shell_info, char *name)
{
	list_t *node = shell_info->env;
	char *ptr;

	while (node)
	{
		ptr = _strstr(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * env_list - compiles the env linked list
 * @shell_info: ....
 * Return: Always 0
 */
int env_list(shell_info_t *shell_info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	shell_info->env = node;
	return (0);
}

/**
 *_setenv - sets a new environment variable
 *@shell_info: input
 *@var: the string env var property
 *@value: the string env var value
 *Return: Always 0
 */
int _setenv(shell_info_t *shell_info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = shell_info->env;
	while (node)
	{
		p = _strstr(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			shell_info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(shell_info->env), buf, 0);
	free(buf);
	shell_info->env_changed = 1;
	return (0);
}


/**
 *_unsetenv - deselects an environment variable
 *@shell_info: input value
 *@var: the string env var property
 *Return: 1 on delete, 0 otherwise
 */
int _unsetenv(shell_info_t *shell_info, char *var)
{
	list_t *node = shell_info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = _strstr(node->str, var);

		if (p && *p == '=')
		{
			shell_info->env_changed = del_at_index(&(shell_info->env), i);
			i = 0;
			node = shell_info->env;
			continue;
		}

		node = node->next;
		i++;
	}
	return (shell_info->env_changed);
}
