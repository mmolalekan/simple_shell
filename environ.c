#include "shell.h"

/**
 * _env - prints the current environment
 * @info: Argument struct.
 * Return: Always 0
 */

int _env(data_t *info)
{
	print_string_list(info->env);
	return (0);
}

/**
 * _getenv - get variable value from environ
 * @info: Argument struct
 * @name: variable name
 * Return: value
 */

char *_getenv(data_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = initial(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * call_setenv - Initialize or modify an environ variable
 * @info: Argument struct
 * Return: 0
 */

int call_setenv(data_t *info)
{
	if (info->argc != 3)
	{
		_errputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * call_unsetenv - Remove an environment variable
 * @info: Argument struct
 * Return: 0
 */

int call_unsetenv(data_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_errputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[1]);
	return (0);
}

/**
 * make_env_list - make a new linked list with environ variables
 * @info: Argument structure
 * Return: 0
 */

int make_env_list(data_t *info)
{
	list_t *var = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_to_end(&var, environ[i], 0);
	info->env = var;
	return (0);
}
