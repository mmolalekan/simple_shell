#include "shell.h"


/**
 * _strchr - finds a character in a string
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}


/**
 * _strstr - Entry point
 * @haystack: input
 * @needle: input
 * Return: Always 0 (Success)
 */
char *_strstr(char *haystack, char *needle)
{
	for (; *haystack != '\0'; haystack++)
	{
		char *l = haystack;
		char *p = needle;

		while (*l == *p && *p != '\0')
		{
			l++;
			p++;
		}

		if (*p == '\0')
			return (haystack);
	}

	return (0);
}

/**
 * _strncmp - compare two strings up to n characters
 *
 * @s1: string 1
 * @s2: string 2
 * @n: number of characters to compare
 * Return: int
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}

/**
 * _getenv - retrieves the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: a pointer to the value of the environment variable,
 * or NULL if the variable is not found
 */
char *_getenv(const char *name)
{
	char *env_value;
	int len = _strlen(name);
	char **env = environ;

	while (*env != NULL)
	{
		if (_strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			env_value = &(*env)[len + 1];
			break;
		}
		env++;
	}
	return (env_value);
}
