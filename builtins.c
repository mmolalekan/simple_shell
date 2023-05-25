#include "shell.h"

/**
 * _history - Display history list, starting at 0.
 * @info: Arguments struct
 * Return: 0
 */

int _history(data_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - set alias to string
 * @info: Arguments struct
 * @str: string alias
 * Return: 1 on error, 0 on success
 */

int unset_alias(data_t *info, char *str)
{
	char *ptr, ch;
	int result;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	result = delete_node_at_index(&(info->alias),
			get_node_at_index(info->alias, node_initial(info->alias, str, -1)));
	*ptr = ch;
	return (result);
}

/**
 * set_alias - Set alias
 * @info: Argument struct
 * @str: new alias
 * Return: 0 on success, 1 on error
 */

int set_alias(data_t *info, char *str)
{
	char *ptrr;

	ptrr = _strchr(str, '=');
	if (!ptrr)
		return (1);
	if (!*++ptrr)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_to_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the node of the alias
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptrr = NULL, *a = NULL;

	if (node)
	{
		ptrr = _strchr(node->str, '=');
		a = node->str;
		for (a = node->str; a <= ptrr; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(ptrr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _alias - alias builtin
 * @info: Argument struct
 * Return: 0
 */
int _alias(data_t *info)
{
	int i = 1;
	char *ptrr = NULL;
	list_t *new_alias = NULL;

	if (info->argc == 1)
	{
		new_alias = info->alias;
		while (new_alias)
		{
			print_alias(new_alias);
			new_alias = new_alias->next;
		}
		return (0);
	}
	while (info->argv[i])
	{
		ptrr = _strchr(info->argv[i], '=');
		if (ptrr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_initial(info->alias, info->argv[i], '='));
		i++;
	}
	return (0);
}
