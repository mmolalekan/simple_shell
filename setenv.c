#include "shell.h"

/**
 * _putenv - Adds or updates an environment variable
 *
 * @name: The name of the environment variable
 * @value: The value of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int _putenv(const char *name, const char *value)
{
	char *env_var;
	size_t name_len, value_len;
	int i;

	name_len = _strlen(name);
	value_len = _strlen(value);

	env_var = malloc(name_len + value_len + 2);

	if (env_var == NULL)
		return (-1);

	_strcpy(env_var, name);
	_strcpy(env_var + name_len, "=");
	_strcpy(env_var + name_len + 1, value);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(name, environ[i], name_len) == 0 && environ[i][name_len] == '=')
		{
			_strcpy(environ[i], env_var);
			free(env_var);
			return (0);
		}
	}

	environ[i] = env_var;
	environ[i + 1] = NULL;

	return (0);
}

/**
 * _setenv - Sets the value of an environment variable.
 * @name: The name of the variable.
 * @value: The new value for the variable.
 * @overwrite: Whether to overwrite the variable if it already exists.
 *
 * Return: 0 on success, or -1 on failure.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
		return (-1);

	size_t name_len = _strlen(name);
	size_t value_len = _strlen(value);
	char *env_str = malloc(name_len + value_len + 2);

	if (env_str == NULL)
		return (-1);

	_memcpy(env_str, name, name_len);
	env_str[name_len] = '=';
	_memcpy(env_str + name_len + 1, value, value_len);
	env_str[name_len + value_len + 1] = '\0';

	if (!overwrite && _getenv(name) != NULL)
	{
		free(env_str);
		return (0);
	}

	if (_putenv(env_str) != 0)
	{
		const char *msg = "Failed to set environment variable.\n";

		write(STDERR_FILENO, msg, _strlen(msg));
		free(env_str);
		return (-1);
	}

	return (0);
}
