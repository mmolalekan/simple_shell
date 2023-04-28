#include "shell.h"

/**
 * _strtok - tokenize a string into smaller strings based on a delimiter
 * @str: pointer to the string to be tokenized
 * @delim: string containing the delimiters
 *
 * Return: pointer to the next token in the string
 */

char *_strtok(char *str, char *delim)
{
	static char *pos;
	char *start, *end;

	if (str != NULL)
		pos = str;

	start = pos;

	while (*pos != '\0')
	{
		end = delim;
		while (*end != '\0')
		{
			if (*pos == *end)
			{
				*pos = '\0';
				pos++;
				return (start);
			}
			end++;
		}
		pos++;
	}

	return (NULL);
}
