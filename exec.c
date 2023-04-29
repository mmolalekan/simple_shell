#include "shell.h"
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>

/**
 * is_space - check for leading and trailing whitespaces
 *
 * @c: character to check
 * Return: int
 */

int is_space(int c)
{
	return (c == ' ' ||
			c == '\t' ||
			c == '\n' ||
			c == '\r' ||
			c == '\f' ||
			c == '\v');
}

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
 * trim_space - remove leading and trailing spaces
 *
 * @input: pointer to string to trim
 * Return: void*
 */

void trim_space(char *input)
{
	size_t len = _strlen(input);
	size_t lead = 0;

	printf("$ %s\n", input);
	while (is_space(input[lead]) && lead < len)
	{
		lead++;
	}
	if (lead > 0)
	{
		_memmove(input, input + lead, len + 1);
		len -= lead;
	}
	while (len > 0 && is_space(input[len - 1]))
	{
		len--;
	}
	input[len] = '\0';
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
	size_t command_count = 0;

	if (_strcmp(argv[0], "exit") == 0)
	exit(EXIT_SUCCESS);
	if ((argv[0][0] == '/') == 1 || argv[0][0] == '.')
	{
		command_count++;
		pid = fork();
		if (pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
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
			command_count++;
			perror("process");
			return (-1);
		}
	}
	else
	{
		handle_p(&command_count, pathname, argv, env);
	}
	return (0);
}

/**
 * handle_p - Handle relative path for executables
 *
 * @cm: num of commands
 * @name: Name of program
 * @argv: argument vector list
 * @env: enviroment variables
 */

void handle_p(size_t *cm, const char *name, char *const argv[], char *const env[])
{
	char *filepath;
	int i;

	char __attribute__((unused)) *new_argv[1024 * sizeof(char)];
	filepath = search_path(argv[0]);
	if (filepath)
	{
		for (i = 0; new_argv[i]; i++)
			new_argv[i] = '\0';
		new_argv[0] = filepath;
		i = 1;
		while (argv[i])
		{
			new_argv[i] = argv[i];
			i++;
		}
		execute(new_argv[0], new_argv, env);
	}
	else
	{
		char str[10];

		++*cm;
		_itoa(*cm, str, 10);
		write(STDERR_FILENO, name, _strlen(name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, str, _strlen(str));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, argv[0], _strlen(argv[0]));
		write(STDERR_FILENO, ": not found", 11);
		_putchar('\n');
	}
}
