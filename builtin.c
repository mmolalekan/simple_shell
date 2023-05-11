#include "shell.h"

/**
 * check_builtin - Check if command entered is builtin and run function
 *
 * @cmd: user command list
 * @buf: buffer
 * Return: 0 if builtin or -1 if not builtin
 */

int check_builtin(char *cmd[], char *buf)
{
	if (_strcmp(cmd[0], "exit") == 0)
	{
		if (!cmd[1])
		e_exit(EXIT_SUCCESS, buf);
		else
		e_exit(atoi(cmd[1]), buf);
	}
	else if (_strcmp(cmd[0], "env") == 0)
	print_env();
	else if (_strcmp(cmd[0], "setenv") == 0)
	{
		_setenv(cmd);
	}
	else if (_strcmp(cmd[0], "unsetenv") == 0)
	_unsetenv(cmd);
	else
	{
		return (-1);
	}
	return (0);
}
