#include "shell.h"

/**
 * search_path - Search for executable file in PATH
 *
 * @str: command to search for
 * Return: pointer to filepath or NULL if no file.
 */

char *search_path(char const *str)
{
	/*get path env*/
	char *path = _getenv("PATH");
	char *path_cpy = malloc(sizeof(char) * _strlen(path));
	/*tokenize the path*/
	char **tokens;
	char *filepath = malloc(sizeof(char) * 1024);
	int i = 0;

	_strcpy(path_cpy, path);
	tokens = tokenize(path_cpy, ":");
	/*search path for command*/
	while (tokens[i])
	{
		_strcpy(filepath, tokens[i]);
		_strcat(filepath, "/");
		_strcat(filepath, str);

		if (access(filepath, X_OK) == 0)
		{
			free(tokens);
			free(path_cpy);
			return (filepath);
		}
		i++;
	}
	free(filepath);
	return (NULL);
}