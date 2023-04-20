#include "shell.h"

/**
 * _strcat - concatenate  a str to another
 * @dest: pointer to destination
 * @src: pointer to source
 * Return: char
 */

char *_strcat(char *dest, char *src)
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
