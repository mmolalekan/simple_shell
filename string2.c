#include "shell.h"

/**
 * _strstr - search for a string
 * @haystack: Pointer to string
 * @needle: pointer to search  string
 * Return:char*
 */

char *_strstr(char *haystack, char *needle)
{
while (*haystack != '\0')
{
char *haypoint = haystack;
char *needlepoint = needle;
while (*haypoint == *needlepoint && *needlepoint != '\0')
{
haypoint++;
needlepoint++;
}
if (*needlepoint == '\0')
return (haystack);
haystack++;
}
return (NULL);
}

/**
 * rev_string - return string reversed
 * @s: pointer
 */

void rev_string(char *s)
{
char rev = s[0];
int counter = 0;
int i;

while (s[counter] != '\0')
counter++;
for (i = 0; i < counter; i++)
{
counter--;
rev = s[i];
s[i] = s[counter];
s[counter] = rev;
}
}
