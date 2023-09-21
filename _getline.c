#include "header.h"

/**
 * input_buf - buffers chained commands
 * @shell_info: struct value
 * @buf: arg
 * @len: arg
 *
 * Return: resulting bytes
 */
ssize_t input_buf(shell_info_t *shell_info, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t length = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		b = getline(buf, &length, stdin);
#else
		b = _getline(shell_info, buf, &length);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0';
				b--;
			}
			shell_info->linecount_flag = 1;
			remove_comment(*buf);
			compile_hist(shell_info, *buf, shell_info->histcount++);
			{
				*len = b;
				shell_info->cmd_buf = buf;
			}
		}
	}
	return (b);
}

/**
 * get_input - gets a line minus the newline
 * @shell_info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(shell_info_t *shell_info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(shell_info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = input_buf(shell_info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(shell_info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(shell_info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			shell_info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - function reads a buffer
 * @shell_info: ...
 * @buf: buffer
 * @i: size
 *
 * Return: value of r
 */
ssize_t read_buf(shell_info_t *shell_info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(shell_info->readfd, buf, BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - prints the next line of input from STDIN
 * @shell_info: ...
 * @ptr: pointer value
 * @length: size
 *
 * Return: s
 */
int _getline(shell_info_t *shell_info, char **ptr, size_t *length)
{
	static char buf[BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(shell_info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

