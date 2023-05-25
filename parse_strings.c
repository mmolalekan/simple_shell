#include "shell.h"

/**
 * is_command - checks if a file is an executable
 * @info: info struct
 * @path: file path
 *
 * Return: 1 true, 0 false
 */

int is_command(data_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_char - duplicates characters
 * @str_path: PATH string
 * @start: start index
 * @stop: end index
 *
 * Return: pointer to new buffer
 */

char *duplicate_char(char *str_path, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (str_path[i] != ':')
			buffer[k++] = str_path[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * search_path - searchs this cmd in the path string
 * @info: Info struct
 * @str_path: Path string
 * @cmd: command
 *
 * Return: cmd path on success, NULL on error or not found
 */

char *search_path(data_t *info, char *str_path, char *cmd)
{
	int i = 0, current_pos = 0;
	char *path;

	if (!str_path)
		return (NULL);
	if ((_strlen(cmd) > 2) && initial(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str_path[i] || str_path[i] == ':')
		{
			path = duplicate_char(str_path, current_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!str_path[i])
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * _strtok - splits a string into words. Repeat delimiters are ignored.
 * @str: input string.
 * @d: delimiter.
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **_strtok_r - splits a string into words
 * @str: input string
 * @d: delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok_r(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
