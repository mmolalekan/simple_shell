#include "shell.h"
/**
 * getline - read an entire line from a file stream
 * @lineptr: pointer to the buffer containing the read line
 * @n: pointer to the size of the buffer
 * @stream: pointer to the input file stream
 * Return: the num of chars read + \n, -1 on error or EOF
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t result;
	size_t cur_len = 0;
	char c;

	if (*lineptr == NULL || *n == 0)
	{
		*n = 120;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	while (1)
	{
		if (read(0, &c, 1) < 1)
		{
			result = -1;
			break;
		}
		if (cur_len >= (*n) - 1)
		{
			*n *= 2;
			char *newptr = malloc(*n);

			if (newptr == NULL)
			{
				result = -1;
				break;
			}
			_memcpy(newptr, *lineptr, cur_len);
			free(*lineptr);
			*lineptr = newptr;
		}
		(*lineptr)[cur_len++] = c;
		if (c == '\n')
		{
			result = cur_len;
			break;
		}
	}
	(*lineptr)[cur_len] = '\0';
	return (result);
}
