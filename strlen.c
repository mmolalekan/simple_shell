#include "shell.h"

/**
 * _strlen - return length of a string
 * @s: pointer
 * Return: int
 */

int _strlen(char *s)
{
int i = 0;
while (*(s + i) != '\0')
{
i++;
}
return (i);
}
