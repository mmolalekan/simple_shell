#include "shell.h"

/**
 * init_data - initialize data_t struct.
 * @info: Argument struct address.
 */

void init_data(data_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_data - sets data_t struct
 * @info: struct address
 * @av: argument vector list
 */

void set_data(data_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = _strtok(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		modify_alias(info);
		modify_vars(info);
	}
}

/**
 * free_data_mem - free data_t struct
 * @info: struct address
 * @all: number of fields to free
 */

void free_data_mem(data_t *info, int all)
{
	free_func(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buff)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_func(info->environ);
			info->environ = NULL;
		free_buff((void **)info->cmd_buff);
		if (info->read_fd > 2)
			close(info->read_fd);
		_putchar(BUFF_FLUSH);
	}
}
