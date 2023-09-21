#include "my_custom_shell.h"

/**
 * is_cmd_chain - checks for cmd chain value
 * @info: struct param
 * @buf: the buffer to check
 * @ptr: address of current position in buffer
 *
 * Return: 1 if chain is delimiter, else 0
 */
int is_cmd_chain(shell_info_ *info, char *buf, size_t *ptr)
{
	size_t checker = *ptr;

	if (buf[checker] == '|' && buf[checker + 1] == '|')
	{
		buf[checker] = 0;
		checker++;
		info->cmd_buff_type = OR;
	}
	else if (buf[checker] == '&' && buf[checker + 1] == '&')
	{
		buf[checker] = 0;
		checker++;
		info->cmd_buff_type = AND;
	}
	else if (buf[checker] == ';')
	{
		buf[checker] = 0;
		info->cmd_buff_type = SEPARATOR;
	}
	else
		return (0);
	*ptr = checker;
	return (1);
}

/**
 * check_chain - operates on previous info
 * @info: struct
 * @buf: ...
 * @ptr: current pointer
 * @i: initial
 * @len: buffer length
 */
void check_chain(shell_info_ *info, char *buf, size_t *ptr, size_t i, size_t len)
{
	size_t checker = *ptr;

	if (info->cmd_buff_type == AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			checker = len;
		}
	}
	if (info->cmd_buff_type == OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			checker = len;
		}
	}

	*ptr = checker;
}

/**
 * update_alias - updates an aliases
 * @info: struct.
 *
 * Return: 1 Success, Else 0
 */
int update_alias(shell_info_ *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}


/**
 * update_string - updates string
 * @old:  string
 * @new: string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int update_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * update_vars - updates var in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int update_vars(shell_info_ *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			update_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			update_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			update_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		update_string(&info->argv[i], _strdup(""));

	}
	return (0);
}
