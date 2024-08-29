#include "shell.h"

/**
 * _ownexit - exits the shell
 * @info: Structure containing potential arguments.
 *	Used to maintain constant function prototype
 * Return: Exit with a given exit status
 *	0 if info.argv[0] != "exit"
 */
int _ownexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2); }
	info->err_num = -1;
	return (-2);
}
/**
 * _owncd - Changes the current directory of the process
 * @info: Structure containing potential arguments.
 *	Used to maintain constant function prototype
 *
 * Return: Always 0
 */
int _owncd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			dir = _getenv(info, "PWD=") ? _getenv(info, "PWD=") : "/";
		chdir_ret = chdir(dir); }
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1); }
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		dir = _getenv(info, "OLDPWD=") ? _getenv(info, "OLDPWD=") : "/";
		chdir_ret = chdir(dir); }
	else
	{
		chdir_ret = chdir(info->argv[1]); }
	if (chdir_ret == -1)
	{
		print_error(info, "cant't cd to ");
		_eputs(info->argv[1]), _eputchar('\n'); }
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024)); }
	return (0);
}
/**
 * _ownhelp - Changes the current directory of the process
 * @info: Structure containing poteintial arguments
 *	Used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int _ownhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
