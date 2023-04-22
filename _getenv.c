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
	char **env, *env_name, *env_value;

	for (env = environ; *env != NULL; env++)
	{
		env_name = strtok(*env, "=");
		env_value = strtok(NULL, "=");

		if (strcmp(env_name, name) == 0)
			return (env_value);
	}

	return (NULL);
}

