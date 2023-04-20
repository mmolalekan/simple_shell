#include "shell.h"
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
