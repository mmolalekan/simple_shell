#include "shell.h"

/**
 * _errputs - prints an output string
 * @str: the string to be printed
 * Return: Nothing
 */

void _errputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_errputchar(str[i]);
		i++;
	}
}
/**
 * _errputchar - writes the character  ch to stderr
 * @ch: the character to print
 * Return: On success 1
 * on error, -1 is returned, and errno is set appropriately
 */
int _errputchar(char ch)
{
	static int i;
	static char buffer[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (ch != BUFF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * _putcfd - writes the character ch to given fd
 * @ch: character
 * @fd: file descriptor
 * Return: on success 1, on error -1 is returned, errno is set appropriately
 */

int _putcfd(char ch, int fd)
{
	static int i;
	static char buffer[WRITE_BUFF_SIZE];

	if (ch == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (ch != BUFF_FLUSH)
		buffer[i++] = ch;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: string to be printed
 * @fd: file descriptor
 * Return: no of char printed
 */

int _putsfd(char *str, int fd)
{
	int i;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putcfd(*str++, fd);
	}
	return (i);
}

/**
 * _erratoi - converts a string to an integer
 * @s: string
 * Return: 0 if no numbers in string, converted int or -1 on error
 */

int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
