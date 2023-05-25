#include "shell.h"

/**
 * get_environ - gets copy of the environ variables
 * @info: Arguments struct
 * Return: copy of the environ list
 */

char **get_environ(data_t *info)
{
	if (!info->environ || info->new_env)
	{
		info->environ = list_to_strings(info->env);
		info->new_env = 0;
	}
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Arguments struct
 * Return: 1 on success, 0 on error
 * @var: variable to delete
 */

int _unsetenv(data_t *info, char *var)
{
	list_t *old_var = info->env;
	size_t i = 0;
	char *ptr;

	if (!old_var || !var)
		return (0);

	while (old_var)
	{
		ptr = initial(old_var->str, var);
		if (ptr && *ptr == '=')
		{
			info->new_env = delete_node_at_index(&(info->env), i);
			i = 0;
			old_var = info->env;
			continue;
		}
		old_var = old_var->next;
		i++;
	}
	return (info->new_env);
}

/**
 * _setenv - main setenv func
 * @info: Arguments struct
 * @var: variable
 * @value: value
 *  Return: Always 0
 */

int _setenv(data_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = initial(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->new_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_to_end(&(info->env), buf, 0);
	free(buf);
	info->new_env = 1;
	return (0);
}
