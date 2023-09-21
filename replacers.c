#include "header.h"

/**
 * is_chain - function checks for char value in buffer
 * @shell_info: struct value
 * @buf: the char to check
 * @p: address of current position in buffer
 *
 * Return: 1 if chain is delimeter, else 0
 */
int is_chain(shell_info_t *shell_info, char *buf, size_t *p)
{
	size_t checker = *p;

	if (buf[checker] == '|' && buf[checker + 1] == '|')
	{
		buf[checker] = 0;
		checker++;
		shell_info->cmd_buf_type = CMD_OR;
	}
	else if (buf[checker] == '&' && buf[checker + 1] == '&')
	{
		buf[checker] = 0;
		checker++;
		shell_info->cmd_buf_type = CMD_AND;
	}
	else if (buf[checker] == ';')
	{
		buf[checker] = 0;
		shell_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = checker;
	return (1);
}

/**
 * check_chain - operates on previous shell_info
 * @shell_info: struct
 * @buf: ...
 * @p: current
 * @i: initial
 * @len: buffer length
 */
void check_chain(shell_info_t *shell_info,
		char *buf, size_t *p, size_t i, size_t len)
{
	size_t checker = *p;

	if (shell_info->cmd_buf_type == CMD_AND)
	{
		if (shell_info->status)
		{
			buf[i] = 0;
			checker = len;
		}
	}
	if (shell_info->cmd_buf_type == CMD_OR)
	{
		if (!shell_info->status)
		{
			buf[i] = 0;
			checker = len;
		}
	}

	*p = checker;
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @shell_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(shell_info_t *shell_info)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell_info->argv[i]; i++)
	{
		if (shell_info->argv[i][0] != '$' || !shell_info->argv[i][1])
			continue;

		if (!_strcmp(shell_info->argv[i], "$?"))
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(convert_number(shell_info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell_info->argv[i], "$$"))
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(shell_info->env, &shell_info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell_info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell_info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old_str: address of old_str string
 * @new_str: new_str string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}
