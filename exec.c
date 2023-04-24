#include "shell.h"
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

/**
 * tokenize - Make command line arguments into tokens
 *
 * @lineptr: String to tokenize
 * @delim: Delimiter
 * Return: pointer to tokenized array
 */

char **tokenize(char *lineptr, char *delim)
{
	char **arr = malloc(sizeof(char) * 1024);
	char *token;
	int i = 1;

	if (arr == NULL)
	{
		perror("arr");
		return (NULL);
	}

	token = strtok(lineptr, delim);
	arr[0] = token;

	while (token != NULL)
	{
		token = strtok(NULL, delim);
		arr[i] = token;
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
	int n, i;

	if ((argv[0][0] == '/') == 1 || argv[0][0] == '.')
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
			return (0);
		}
		else
		{
			perror("process");
			return (-1);
		}
	}
	else
	{
		char *filepath;
		char __attribute__((unused)) *new_argv[1024 * sizeof(char)];

		filepath = search_path(argv[0]);
		/*for (i = 0; )*/
		if (filepath)
		{
			new_argv[0] = filepath;
			i = 1;
			while (argv[i])
			{
				new_argv[i] = NULL;
				new_argv[i] = argv[i];
				printf("%s\n", new_argv[i]);
				i++;
			}
			execute(new_argv[0], new_argv, env);
		}
		else
		{
			write(STDERR_FILENO, pathname, _strlen(pathname));
			write(STDERR_FILENO, ": not found", 12);
			_putchar('\n');
		}
	}
	return (0);
}
