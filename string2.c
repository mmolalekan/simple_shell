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

/**
 * _strncat - concatenate  a str to another
 * @dest: pointer to destination
 * @src: pointer to source
 * @n: number of characters to concate
 * Return: char
 */

char *_strncat(char *dest, char *src, int n)
{
	int counter;
	int DESTINATION_LENGTH = 0;
	char *tmp_dest = dest;

	while (*dest != '\0')
	{
		DESTINATION_LENGTH++;
		dest++;
	}
	counter = 0;
	while (counter < n && src[counter] != '\0')
	{
		tmp_dest[DESTINATION_LENGTH] = src[counter];
		counter++;
		DESTINATION_LENGTH++;
	}
	tmp_dest[DESTINATION_LENGTH] = '\0';
	return (tmp_dest);
}

/**
 * _strncpy - copy  a str to another
 * @dest: pointer to destination
 * @src: pointer to source
 * @n: number of characters to concate
 * Return: char
 */

char *_strncpy(char *dest, char *src, int n)
{
	char *tmp_dest = dest;
	int counter = 0;

	while (counter < n && src[counter] != '\0')
	{
		tmp_dest[counter] = src[counter];
		counter++;
	}
	while (counter < n)
	{
		tmp_dest[counter] = '\0';
		counter++;
	}
	return (tmp_dest);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
