#include "shell.h"

/**
 * print_err - prints an error message
 * @info: arguments struct
 * @estr: error msg
 */

void print_err(data_t *info, char *estr)
{
	_errputs(info->filename);
	_errputs(": ");
	print_int(info->line_count, STDERR_FILENO);
	_errputs(": ");
	_errputs(info->argv[0]);
	_errputs(": ");
	_errputs(estr);
}

/**
 * print_int - function prints a decimal number
 * @input: input
 * @fd: file descriptor
 * Return: number of printed character
 */

int print_int(int input, int fd)
{
	int (*__putc)(char) = _putchar;
	int i, count = 0;
	unsigned int _absolute_, current;

	if (fd == STDERR_FILENO)
		__putc = _errputchar;
	if (input < 0)
	{
		_absolute_ = -input;
		__putc('-');
		count++;
	}
	else
		_absolute_ = input;
	current = _absolute_;
	i = 1000000000;
	while (i > 1)
	{
		if (_absolute_ / i)
		{
			__putc('0' + current / i);
			count++;
		}
		current %= i;
		i /= 10;
	}
	__putc('0' + current);
	count++;
	return (count);
}
/**
 * convert_number - converts int to string
 * @num: number
 * @base: base
 * @flags: flags
 * Return: pointer to string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *num_str;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	num_str = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = num_str[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_handler - function replaces first instance of '#' with '\0'
 * @buffer: address of the string to modify
 * Return: 0;
 */

void comment_handler(char *buffer)
{
	int i = 0;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}

/**
 * free_buff - free a pointer
 * @ptr: pointer to memory address to be freed
 *
 * Return: 1 on success, 0 on error.
 */

int free_buff(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
