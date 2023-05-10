#include "shell.h"

int check_builtin(char *cmd[], char *buf)
{
	if (_strcmp(cmd[0], "exit") == 0)
	e_exit(EXIT_SUCCESS, buf);
	else if (_strcmp(cmd[0], "env") == 0)
	print_env();
	else
	{
		return (-1);
	}
	return (0);
}