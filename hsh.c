#include "shell.h"

/**
 * display_prompt - displays prompt if in interactive mode
 *
 */

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
		fflush(stdout);
	}
}

/**
 * main - Interactive shell
 *
 * @ac: argument count
 * @av: Argument list
 * @env: Environment variables
 * Return: int
 */

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	ssize_t nread;

	(void)ac;
	(void)**av;
	loop(av, buffer, &nread, env);
	if (nread == -1)
	{
		write(STDOUT_FILENO, "", 0);
	}
	free(buffer);
	return (EXIT_SUCCESS);
}

/**
 * loop - the shell loop
 *
 * @av: Argument vector
 * @buffer: Buffer
 * @nread: number of characters read
 * @env: environment variable
 */

void loop(char **av, char *buffer, ssize_t *nread, char **env)
{
	char *argv[100];
	size_t n = 0;
	int i = 0;

	display_prompt();
	while ((*nread = getline(&buffer, &n, stdin)) != -1)
	{
		if (buffer[0] == '\n')
		{
			display_prompt();
			continue;
		}
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\n')
				buffer[i] = '\0';
		}
		i = 0;
		argv[i] = strtok(buffer, " ");
		while (argv[i] != NULL)
		{
			i++;
			argv[i] = strtok(NULL, " ");
		}
		if (i > 0)
		{
			if (execute(av[0], argv, env) && !(isatty(STDIN_FILENO)))
			{
				exit(127);
			}
		}
		display_prompt();
	}
}
