#include "header.h"


/**
 * _chdir - change the current directory
 * @shell_info: input
 *  Return: Always 0
 */
int _chdir(shell_info_t *shell_info)
{
	char *str, *dir, buf[BUF_SIZE];
	int dir_addr;

	str = getcwd(buf, BUF_SIZE);
	if (!str)
		_puts("Failed to get cmd\n");
	if (!shell_info->argv[1])
	{
		dir = _getenv(shell_info, "HOME=");
		if (!dir)
			dir_addr = chdir((dir = _getenv(shell_info, "PWD=")) ? dir : "/");
		else
			dir_addr = chdir(dir);
	}
	else if (_strcmp(shell_info->argv[1], "-") == 0)
	{
		if (!_getenv(shell_info, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shell_info, "OLDPWD=")), _putchar('\n');
		dir_addr = chdir((dir = _getenv(shell_info, "OLDPWD=")) ? dir : "/");
	}
	else
		dir_addr = chdir(shell_info->argv[1]);
	if (dir_addr == -1)
	{
		print_error(shell_info, "can't change to this dir ");
		_putts(shell_info->argv[1]), _puttchar('\n');
	}
	else
	{
		_setenv(shell_info, "OLDPWD", _getenv(shell_info, "PWD="));
		_setenv(shell_info, "PWD", getcwd(buf, BUF_SIZE));
	}
	return (0);
}

/**
 * _exit_sh - exits the shell
 * @shell_info: ditto
 *  Return: exits(0), if shell_info.argv[0] != "exit"
 */
int _exit_sh(shell_info_t *shell_info)
{
	int errnum;

	if (shell_info->argv[1])
	{
		errnum = _erratoi(shell_info->argv[1]);
		if (errnum == -1)
		{
			shell_info->status = 2;
			print_error(shell_info, "Unwanted number: ");
			_putts(shell_info->argv[1]);
			_puttchar('\n');
			return (1);
		}
		shell_info->errors = _erratoi(shell_info->argv[1]);
		return (-2);
	}
	shell_info->errors = -1;
	return (-2);
}
/**
 * _help_ - entry point
 * @shell_info: ...
 *  Return: Always 0
 */
int _help_(shell_info_t *shell_info)
{
	char **arg_array;

	arg_array = shell_info->argv;
	_puts("Help\n");
	if (0)
		_puts(*arg_array);
	return (0);
}
