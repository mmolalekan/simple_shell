#include "shell.h"
/**
 * input_buff - chained commands to buffer
 * @info: Argument struct
 * @buff: buffer
 * @len: len var.
 * Return: bytes read
 */
ssize_t input_buff(data_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = _getline(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->lc_flag = 1;
			comment_handler(*buff);

			make_history_list(info, *buff, info->history_count++);
			/* if (_strchr(*buff, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buff = buff;
			}
		}
	}
	return (r);
}

/**
 * getinput - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getinput(data_t *info)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_ptr = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	r = input_buff(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;
		check_chain(info, buffer, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buff_type = CMD_NORM;
		}
		*buf_ptr = p;
		return (_strlen(p));
	}
	*buf_ptr = buffer;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: Argument struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */

ssize_t read_buf(data_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->read_fd, buf, READ_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(data_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_SIZE];
	static size_t i, len;
	size_t m;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_ptr = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	m = c ? 1 + (unsigned int)(c - buf) : len;
	new_ptr = _realloc(p, s, s ? s + m : m + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_ptr, buf + i, m - i);
	else
		_strncpy(new_ptr, buf + i, m - i + 1);

	s += m - i;
	i = m;
	p = new_ptr;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
