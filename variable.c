#include "shell.h"
/**
 * is_chain -checks if current char in buffer is a chain delimiter
 * @info: info struct
 * @buf: char buffer
 * @p: current position in buf
 * Return: 1 true, 0 false
 */
int is_chain(data_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks if chaining should continue based on last status
 * @info: info struct
 * @buf: character buffer
 * @p: current position in buffer
 * @i: start position in buffer
 * @len: length of buffer
 */

void check_chain(data_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * modify_alias - replaces an aliases in the list
 * @info: argument struct
 * Return: 1 on success, 0 on error
 */

int modify_alias(data_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_initial(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * modify_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 on success, 0 on failure
 */

int modify_vars(data_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			modify_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			modify_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_initial(info->env, &info->argv[i][1], '=');
		if (node)
		{
			modify_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		modify_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * modify_string - modifies a string
 * @old: old string
 * @new: new string
 *
 * Return: 1 success, 0 error
 */

int modify_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
