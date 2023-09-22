#include "header.h"

/**
 * prints_cmd - determines if a file is an executable command
 * @sh: structnfo struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int prints_cmd(shell_t *sh, char *path)
{
	struct stat init;

	(void)sh;
	if (!path || stat(path, &init))
		return (0);

	if (init.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_double - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *char_double(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int idx = 0, key = 0;

	for (key = 0, idx = start; idx < stop; idx++)
		if (pathstr[idx] != ':')
			buffer[key++] = pathstr[idx];
	buffer[key] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @sh: structnfo struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(shell_t *sh, char *pathstr, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _strstr(cmd, "./"))
	{
		if (prints_cmd(sh, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = char_double(pathstr, current, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (prints_cmd(sh, path))
				return (path);
			if (!pathstr[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
