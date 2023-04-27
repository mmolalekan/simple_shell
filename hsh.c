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
	_putchar('$');
	_putchar(' ');
	while ((nread = getline(&buffer, &n, stdin))!= -1)
	{
		if (nread == 0)
		break;
		if (buffer[0] == '\n')
		continue;
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
		execute(av[0], argv, env);
		write(STDOUT_FILENO, "$ ", 2);
	}
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	return (EXIT_SUCCESS);
}
