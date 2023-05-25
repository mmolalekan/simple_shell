#include "shell.h"

/**
 * _strcpy - copies src to dest
 * @dest: destination
 * @src: source
 *
 * Return: dest
 */

char *_strcpy(char *dest, char *src)
{
int i = 0;

if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the new string
 */

char *_strdup(const char *str)
{
int len = 0;
char *result;

if (str == NULL)
return (NULL);
while (*str++)
len++;
result = malloc(sizeof(char) * (len + 1));
if (!result)
return (NULL);
for (len++; len--;)
result[len] = *--str;
return (result);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * _putchar - writes a character to stdout
 * @c: character to write
 *
 * Return: Always 1.
 */

int _putchar(char c)
{
static int i;
static char buf[WRITE_BUFF_SIZE];

if (c == BUFF_FLUSH || i >= WRITE_BUFF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUFF_FLUSH)
buf[i++] = c;
return (1);
}


/**
 *_strncpy - copies a string
 *@dest: destination
 *@src: source
 *@n: amount of characters to be copied
 *Return: pointer to destination string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}
