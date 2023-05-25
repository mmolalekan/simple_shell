#include "shell.h"

/**
 * _isatty - returns true if shell is _isatty mode
 * @info: struct address
 * Return: 1 if _isatty mode, 0 otherwise
 */

int _isatty(data_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * is_delim - checks if character is delimiter
 * @ch: character
 * @delim: delimiter
 * Return: 1 if true, 0 if false
 */

int is_delim(char ch, char *delim)
{
	for (; *delim;)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 * _isalpha - check for alphabetic character
 * @ch: the character to input
 * Return: 1 if ch is alphabetic, 0 otherwise
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') ||
	 (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i = 0, sign = 1, flag = 0, output;
	unsigned int res = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
		i++;
	}
	if (sign == -1)
		output = -res;
	else
		output = res;
	return (output);
}

