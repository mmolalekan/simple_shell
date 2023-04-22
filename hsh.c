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
	char *argv[] = {NULL, NULL};
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
		execute(buffer, argv, env);
	}
	return (0);
}
