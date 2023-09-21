#include "header.h"

/**
 * get_hist - gets the file history
 * @shell_info: input value
 *
 *
 * Return: the buffer holding the file
 */

char *get_hist(shell_info_t *shell_info)
{
	char *buf, *dir;

	dir = _getenv(shell_info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}


/**
 * read_hist - reads history from file
 * @shell_info: inpt value
 *
 *
 * Return: 1 Success, Else -1
 */
int read_hist(shell_info_t *shell_info)
{
	int i, end = 0;
	int line_len = 0;
	ssize_t fd, rlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist(shell_info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			compile_hist(shell_info, buf + end, line_len++);
			end = i + 1;
		}
	if (end != i)
		compile_hist(shell_info, buf + end, line_len++);
	free(buf);
	shell_info->histcount = line_len;
	while (shell_info->histcount-- >= MAX_HISTORY)
		del_at_index(&(shell_info->history), 0);
	update_hist(shell_info);
	return (shell_info->histcount);
}

/**
 * write_hist - appends to an existing file
 * @shell_info: input value
 *
 *
 * Return: 1 (Success), Else -1
 */
int write_hist(shell_info_t *shell_info)
{
	ssize_t fd;
	char *filename = get_hist(shell_info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = shell_info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}
/**
 * compile_hist - adds an entry to a history linked list
 * @shell_info: ditto
 * @buf: buffer value
 * @linecount: the history linecount
 *
 *
 * Return: Always 0
 */
int compile_hist(shell_info_t *shell_info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (shell_info->history)
		node = shell_info->history;
	add_node_end(&node, buf, linecount);

	if (!shell_info->history)
		shell_info->history = node;
	return (0);
}

/**
 * update_hist - function updates the history linked lists
 * @shell_info: dito
 *
 *
 * Return: the updated history list
 */
int update_hist(shell_info_t *shell_info)
{
	list_t *node = shell_info->history;
	int x = 0;

	while (node)
	{
		node->i = x++;
		node = node->next;
	}
	return (shell_info->histcount = x);
}
