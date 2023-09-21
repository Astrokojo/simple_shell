#include "header.h"

/**
 * prints_cmd - determines if a file is an executable command
 * @shell_info: the shell_info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int prints_cmd(shell_info_t *shell_info, char *path)
{
	struct stat init;

	(void)shell_info;
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
 * find_path - finds the PATH in a string
 * @shell_info: the shell_info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(shell_info_t *shell_info, char *pathstr, char *cmd)
{
	int i = 0, current = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _strstr(cmd, "./"))
	{
		if (prints_cmd(shell_info, cmd))
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
			if (prints_cmd(shell_info, path))
				return (path);
			if (!pathstr[i])
				break;
			current = i;
		}
		i++;
	}
	return (NULL);
}
