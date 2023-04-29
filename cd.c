#include "shell.h"

/**
 * cd - Changes the current directory of the process.
 * @dir: The directory to change to.
 *
 * Return: On success, 0 is returned. On error, -1 is returned.
 */
int cd(const char *dir)
{
	char *home = NULL, *prev = NULL;
	char cwd[1024];

	if (!dir)
		home = _getenv("HOME");
	else if (!_strcmp((void *) dir, "-"))
	{
		prev = _getenv("OLDPWD");
		if (!prev)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
			return (-1);
		}
	}
	else
		home = (char *)dir;

	if (prev)
	{
		if (chdir(prev) != 0)
		{
			char error_msg[1024] = "cd: can't cd to ";
			_strcat(error_msg, prev);
			_strcat(error_msg, "\n");
			write(STDERR_FILENO, error_msg, strlen(error_msg));
			return (-1);
		}
		write(STDOUT_FILENO, prev, strlen(prev));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
		if (chdir(home) != 0)
		{
			char error_msg[1024] = "cd: can't cd to ";
			_strcat(error_msg, home);
			_strcat(error_msg, "\n");
			write(STDERR_FILENO, error_msg, strlen(error_msg));
			return (-1);
		}
		write(STDOUT_FILENO, home, strlen(home));
		write(STDOUT_FILENO, "\n", 1);
	}

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		_setenv("PWD", cwd, 1);
	else
	{
		perror("getcwd() error");
		return (-1);
	}

	if (prev)
		_setenv("OLDPWD", prev, 1);
	else
		_setenv("OLDPWD", home, 1);

	return (0);
}
