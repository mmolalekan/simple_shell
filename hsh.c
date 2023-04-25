#include "shell.h"

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
	char *argv[100];
	size_t n = 0;
	ssize_t nread;
	int i = 0;

	(void) ac;
	(void) **av;
	while (1)
	{
		buffer = NULL;
		_putchar('$');
		_putchar(' ');
		nread = getline(&buffer, &n, stdin);
		if (nread == -1)
		{
			write(2, buffer, nread);
			perror("");
			exit(98);
		}
		if (buffer[0] == '\n')
		continue;
		for (i = 0; i < nread; i++)
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
		execute(av[0], argv, env);
	}
	free(buffer);
	return (0);
}
