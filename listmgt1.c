#include "shell.h"

/**
 * list_len - get length of linked list
 * @h: pointer to first node
 * Return: list size
 */

size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - converts linked list to array of strings
 * @head: head node
 *
 * Return: string array
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **str_list;
	char *str;

	if (!head || !i)
		return (NULL);
	str_list = malloc(sizeof(char *) * (i + 1));
	if (!str_list)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(str_list[j]);
			free(str_list);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		str_list[i] = str;
	}
	str_list[i] = NULL;
	return (str_list);
}
/**
 * print_list - prints all elements of a linked list
 * @h: head node
 *
 * Return: list size
 */

size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_initial - get node with matching initial char
 * @node: head node ptr
 * @prefix: string to match
 * @c: next character
 *
 * Return: node or null
 */

list_t *node_initial(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = initial(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_at_index - gets the index of a node
 * @head: head node
 * @node: current node
 *
 * Return: index of node or -1
 */
ssize_t get_node_at_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
