#include "shell.h"

/**
 * cd - change directory
 *
 * @path: path to go to
 * Return: int
 */

int cd(char *path)
{
	char *dir = NULL;
	char *home = _getenv("HOME");
	char cwd[1024];

	if (!path)
	{
		dir = home;
	}
	else if (path)
	{
		if (strcmp(path, "-") == 0)
		{
			dir = _getenv("OLDPWD");
		}
		else
		{
			dir = path;
		}
	}
	else
	{
		printf("Usage: cd [DIRECTORY]\n");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (chdir(dir) == -1)
	{
		perror("chdir() error");
		return 1;
	}
	if (setenv("OLDPWD", cwd, 1) == -1)
	{
		perror("setenv() error");
		return 1;
	}
	if (setenv("PWD", getcwd(cwd, sizeof(cwd)), 1) == -1)
	{
		perror("setenv() error");
		return 1;
	}
	return 0;
}

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
	char *path_cpy;
	/*tokenize the path*/
	char **tokens;
	char *filepath;
	int i = 0;

	if (!path)
		return (NULL);
	path_cpy = malloc(sizeof(char) * (_strlen(path) + 1));
	filepath = malloc(sizeof(char) * 1024);
	_strcpy(path_cpy, path);
	tokens = tokenize(path_cpy, ":");
	/*search path for command*/
	while (tokens[i])
	{
		filepath[i] = '\0';
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
	free(tokens);
	free(path_cpy);
	free(filepath);
	return (NULL);
}
