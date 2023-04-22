#include "shell.h"
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

/**
 * cpy_env - copy environment variables
 *
 * @list: Pointer to env
 * Return: pointer to new arr
 */

char **cpy_env(char **list)
{
	char **list_cpy = malloc(256 * sizeof(char));
	int i = 0;

	while (list[i])
	{
		list_cpy[i] = list[i];
		i++;
	}
	return (list_cpy);
}

/**
 * tokenize - Make command line arguments into tokens
 *
 * @lineptr: String to tokenize
 * Return: pointer to tokenized array
 */

char **tokenize(char **lineptr)
{
	char **arr = malloc(sizeof(char) * sizeof(*lineptr));
	char *token;
	int i = 1;

	token = strtok(*lineptr, " ");
	arr[0] = token;

	while (token != NULL)
	{
		token = strtok(NULL, " ");
		arr[i] = token;
		i++;
	}
	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}

	return (arr);
}


/**
 * execute - execute programs
 *
 * @pathname: path to execute file
 * @argv: Argument list
 * @env: Environment variable
 * Return: int
 */
int execute(const char *pathname, char *const argv[], char *const env[])
{
	pid_t pid;
	int n;

	if ((argv[0][0] == '/') == 1)
	{
	pid = fork();
	if (pid == 0)
	{
		if (execve(pathname, argv, env) == -1)
		{
			perror("Execution");
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &n, 0);
	}
	else
	{
		perror("process");
		return (-1);
	}
	}
	return (0);
}
