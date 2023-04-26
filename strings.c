#include "shell.h"

/**
 * _strcat - concatenate  a str to another
 * @dest: pointer to destination
 * @src: pointer to source
 * Return: char
 */

char *_strcat(char *dest, char const *src)
{
int DESTINATION_LENGTH = 0;
char *tmp_dest = dest;
while (*dest != '\0')
{
DESTINATION_LENGTH++;
dest++;
}
while (*src != '\0')
{
tmp_dest[DESTINATION_LENGTH] = *src;
src++;
DESTINATION_LENGTH++;
}
if (*src == '\0')
tmp_dest[DESTINATION_LENGTH] = *src;
return (tmp_dest);
}

/**
 * _strlen - return length of a string
 * @s: pointer
 * Return: int
 */

int _strlen(char const *s)
{
int i = 0;
while (*(s + i) != '\0')
{
i++;
}
return (i);
}

/**
 * _strcpy - copies str to dest
 * @dest: pointer
 * @src: source of copy
 * Return: char pointer
 */

char *_strcpy(char *dest, char *src)
{
char *main_dest = dest;
while (*src != '\0')
{
*dest = *src;
dest++;
src++;
}
*dest = '\0';
return (main_dest);
}


/**
 * _strcmp - compare two strings
 * @s1: string to compare
 * @s2: string to compare against
 * Return: int
 */

int _strcmp(char *s1, char *s2)
{
int count = 0;
while (s1[count] != '\0' && s2[count] != '\0')
{
if (s1[count] != s2[count])
{
return (s1[count] - s2[count]);
}
count++;
}
return (0);
}


/**
 * _strdup - duplicate to new memory space location
 * @str: char
 * Return: 0
 */
char *_strdup(char *str)
{
	char *aaa;
	int i, r = 0;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
		i++;

	aaa = malloc(sizeof(char) * (i + 1));

	if (aaa == NULL)
		return (NULL);

	for (r = 0; str[r]; r++)
		aaa[r] = str[r];

	return (aaa);
}

