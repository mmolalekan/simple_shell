#include "shell.h"

/**
 * check_builtin - Check if command entered is builtin and run function
 *
 * @cmd: user command list
 * @buf: buffer
 * @status: exit status
 * Return: 0 if builtin or -1 if not builtin
 */

int check_builtin(char *cmd[], char *buf, int status)
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
	_setenv(cmd);
	else if (_strcmp(cmd[0], "unsetenv") == 0)
	_unsetenv(cmd);
	else if (_strcmp(cmd[0], "cd") == 0)
	cd(cmd[1]);
	else if (_strcmp(cmd[0], "echo") == 0 && strchr(cmd[1], '$'))
	var_replacement(cmd[1], status);
	else
	return (-1);
	return (0);
}

/**
 * var_replacement - Handle Variable replacement
 *
 * @variable: variable
 * @status: exit status
 */

void var_replacement(char *variable, int status)
{
	if (_strcmp("$?", variable) == 0)
	{
		char status_str[5];

		_itoa(status, status_str, 10);
		write(STDOUT_FILENO, status_str, _strlen(status_str));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (_strcmp("$$", variable) == 0)
	{
		char pid_str[10];
		pid_t pid = getpid();

		_itoa(pid, pid_str, 10);
		write(STDOUT_FILENO, pid_str, _strlen(pid_str));
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (_strcmp("$PATH", variable) == 0)
	{
		print_var("PATH");
	}
	else if (_strcmp("$HOME", variable) == 0)
	{
		print_var("HOME");
	}
	else if (_strcmp("$PWD", variable) == 0)
	{
		print_var("PWD");
	}
	else if (_strcmp("$USER", variable) == 0)
	{
		print_var("USER");
	}
	else if (_strcmp("$LANG", variable) == 0)
	{
		print_var("LANG");
	}
	else
	write(STDOUT_FILENO, "", 1);
}

/**
 * print_var - print variable
 *
 * @name: name of variable
 */

void print_var(const char *name)
{
	char *env_var = _getenv(name);

	write(STDOUT_FILENO, env_var, _strlen(env_var));
	write(STDOUT_FILENO, "\n", 1);
}
