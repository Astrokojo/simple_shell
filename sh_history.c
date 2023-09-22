#include "header.h"

/**
 * hist_ret - retrieves file history
 * @sh: input value
 *
 * Return: retrieved history file
 */

char *hist_ret(shell_t *sh)
{
	char *buff, *dir;

	dir = _getenv(sh, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HISTORY_FILE);
	return (buff);
}

/**
 * write_hist - appends to an existing file
 * @sh: input value
 *
 * Return: 1 on success, else -1
 */
int write_hist(shell_t *sh)
{
	ssize_t fd;
	char *filename = hist_ret(sh);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = sh->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - reads history from file
 * @sh: ...
 *
 * Return: ...
 */
int read_hist(shell_t *sh)
{
	int i, end = 0;
	int line_len = 0;
	ssize_t fd, rlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = hist_ret(sh);

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
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			compile_hist(sh, buff + end, line_len++);
			end = i + 1;
		}
	if (end != i)
		compile_hist(sh, buff + end, line_len++);
	free(buff);
	sh->histcount = line_len;
	while (sh->histcount-- >= MAX_HISTORY)
		del_node(&(sh->history), 0);
	update_hist(sh);
	return (sh->histcount);
}

/**
 * compile_hist - adds an entry to a history linked list
 * @sh: ...
 * @buf: buffer value
 * @linecount: the history linecount
 *
 * Return: Always 0
 */
int compile_hist(shell_t *sh, char *buf, int linecount)
{
	list_t *node = NULL;

	if (sh->history)
		node = sh->history;
	add_node_end(&node, buf, linecount);

	if (!sh->history)
		sh->history = node;
	return (0);
}

/**
 * update_hist - function updates the history linked lists
 * @sh: ...
 *
 * Return: the updated history list
 */
int update_hist(shell_t *sh)
{
	list_t *node = sh->history;
	int x = 0;

	while (node)
	{
		node->i = x++;
		node = node->next;
	}
	return (sh->histcount = x);
}
