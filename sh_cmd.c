#include "header.h"

/**
 * _exit_ - exits the shell
 * @sh: ...
 *  Return: exits with a given exit status
 *         (0) if sh.argv[0] != "exit"
 */
int _exit_(shell_t *sh)
{
	int ch;

	if (sh->argv[1])
	{
		ch = _atoi(sh->argv[1]);
		if (ch == -1)
		{
			sh->status = 2;
			print_err(sh, "Illegal number: ");
			_putts(sh->argv[1]);
			_puttchar('\n');
			return (1);
		}
		sh->errors = _atoi(sh->argv[1]);
		return (-2);
	}
	sh->errors = -1;
	return (-2);
}

/**
 * _cd_ - changes the current directory of the process
 * @sh: details
 *  Return: Always 0
 */
int _cd_(shell_t *sh)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!sh->argv[1])
	{
		dir = _getenv(sh, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(sh, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(sh->argv[1], "-") == 0)
	{
		if (!_getenv(sh, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(sh, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(sh, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(sh->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(sh, "can't cd to ");
		_putts(sh->argv[1]), _puttchar('\n');
	}
	else
	{
		_setenv(sh, "OLDPWD", _getenv(sh, "PWD="));
		_setenv(sh, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help_ - entry point
 * @sh: ...
 *  Return: Always 0
 */
int _help_(shell_t *sh)
{
	char **arg_array;

	arg_array = sh->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
