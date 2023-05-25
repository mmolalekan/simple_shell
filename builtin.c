#include "shell.h"

/**
 * e_exit - exits the shell
 * @info: arguments struct
 * Return: exit status (0) if info.argv[0] != "exit"
 */

int e_exit(data_t *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = _erratoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			_errputs(info->argv[1]);
			_errputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * cd - changes the current directory of the process
 * @info: Arguments struct
 * Return: 0 success, 1 on error
 */

int cd(data_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_result;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("No such directory\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_result =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_result = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(info->argv[1]);
	if (chdir_result == -1)
	{
		print_err(info, "cannot cd to ");
		_errputs(info->argv[1]), _errputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * _help - helps in changing the current directory of the process
 * @info: Arguments struct
 * Return: 0
 */
int _help(data_t *info)
{
	char **args;

	args = info->argv;
	if (0)
		_puts(*args);
	return (0);
}

/**
 * _strchr - locates a character in a string
 * @s: string
 * @c: character
 * Return: pointer to char in string or NULL if not found
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
