#include "shell.h"

/**
 * get_data_history - gets the history file
 * @info: info struct
 * Return: history file
 */

char *get_data_history(data_t *info)
{
	char *buff, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: info struct
 * Return: 1 on success, else -1
 */

int write_history(data_t *info)
{
	ssize_t fd;
	char *filename = get_data_history(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putcfd('\n', fd);
	}
	_putcfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: info struct
 *
 * Return: history_file_line_count on success, 0 elseway
 */

int read_history(data_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, read_len, f_size = 0;
	struct stat st;
	char *buff = NULL, *filename = get_data_history(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	read_len = read(fd, buff, f_size);
	buff[f_size] = 0;
	if (read_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			make_history_list(info, buff + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		make_history_list(info, buff + last, linecount++);
	free(buff);
	info->history_count = linecount;
	while (info->history_count-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	adjust_history_list(info);
	return (info->history_count);
}

/**
 * make_history_list - adds entry to a history linked list
 * @info: Argument struct
 * @buff: buffer
 * @linecount: the history line count
 *
 * Return: 0
 */

int make_history_list(data_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_to_end(&node, buff, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * adjust_history_list - adjusts the history linked list after changes
 * @info: info struct
 *
 * Return: new history_file_line_count
 */

int adjust_history_list(data_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
