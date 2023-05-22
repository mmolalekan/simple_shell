#include "shell.h"

/**
 * _getenv - retrieves the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: a pointer to the value of the environment variable,
 * or NULL if the variable is not found
 */
char *_getenv(const char *name)
{
	char *env_value;
	int len = _strlen(name);
	char **env = environ;

	while (*env != NULL)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			env_value = &(*env)[len + 1];
			break;
		}
		env++;
	}
	return (env_value);
}

/**
 * _setenv - Set environment variable
 *
 * @cmd: command list
 * Return: 0 on success and -1 on error
 */

int _setenv(char *cmd[])
{
	int i = 0;

	if (!cmd[1] || !cmd[2])
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n", 30);
		return (-1);
	}
	while (environ[i])
	{
		char *linker;
		size_t num_byte_matched;

		linker = _strchr(environ[i], '=');
		if (linker == NULL)
		{
			return (-1);
		}
		num_byte_matched = linker - environ[i];
		if (_strncmp(environ[i], cmd[1], num_byte_matched) == 0)
		{
			_strcpy(linker + 1, cmd[2]);
			return (0);
		}
		i++;
	}
	environ[i] = malloc(sizeof(char) * _strlen(cmd[1]) + _strlen(cmd[2]) + 2);
	if (!environ[i])
	return (-1);
	else
	{
		_memset(environ[i], 0, _strlen(cmd[1]) + _strlen(cmd[2]) + 2);
		_strcat(environ[i], cmd[1]);
		_strcat(environ[i], "=");
		_strcat(environ[i], cmd[2]);
	}
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - delete variable from environ list
 *
 * @cmd: command list
 * Return: 0 on success and -1 on error
 */

int _unsetenv(char *cmd[])
{
	int i = 0;

	if (!cmd[1])
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", 26);
		return (-1);
	}
	while (environ[i])
	{
		char *linker = strchr(environ[i], '=');
		size_t n = linker - environ[i];

		if (strncmp(environ[i], cmd[1], n) == 0)
		{
			while (environ[i])
			{
				environ[i] = environ[i + 1];
			}
			return (0);
		}
		i++;
	}
	return (0);
}


/**
 * print_env - print environment
 *
 */

void print_env(void)
{
	int i = 0;

	while (environ && environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
