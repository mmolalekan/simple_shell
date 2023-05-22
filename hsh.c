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
	return (0);
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
	char *argv[100], *multi_command[1024];
	size_t n = 0;
	int i = 0, has_AND;

	display_prompt();
	while ((*nread = getline(&buffer, &n, stdin)) != -1)
	{
		if (buffer[0] == '\n')
		{
			display_prompt();
			free(buffer);
			buffer = NULL;
			continue;
		}
		for (i = 0; buffer[i]; i++)
		{
			if (buffer[i] == '\n')
				buffer[i] = '\0';
		}
		i = 0;
		has_AND = check_multi_command(buffer, multi_command);
		run_exec(buffer, av, env, argv, multi_command, has_AND);
		display_prompt();
	}
}

void run_exec(
	char *buffer,
	char **av,
	char **env,
	char *argv[],
	char *multi_command[],
	int has_AND)
{
	int i, j = 0, b = 0;

	do
	{
		i = 0;
		argv[i] = strtok(buffer, " ");
		while (argv[i] != NULL)
		{
			++i;
			argv[i] = strtok(NULL, " ");
		}
		argv[i] = NULL;
		if (i > 0)
		{
			if (execute(av[0], argv, env, buffer, &b) == 127 && !(isatty(STDIN_FILENO)))
			{
				exit(127);
				free(buffer);
			}
		}
		if (b == 1 && has_AND == 1)
		break;
		++j;
		buffer = NULL;
		buffer = multi_command[j];
	} while (multi_command[j] != NULL);
}

int check_multi_command(char *buffer, char *multi_command[])
{
	int i = 0;
	char *linker;
	if (strchr(buffer, ';'))
	{
		multi_command[i] = strtok(buffer, ";");
		while (multi_command[i] != NULL)
		{
			i++;
			multi_command[i] = strtok(NULL, ";");
		}		
		multi_command[i] = NULL;
		return (0);
	}
	linker = _strstr(buffer, "||");
	if (linker)
	{
		multi_command[i] = strtok(buffer, "||");
		while (multi_command[i] != NULL)
		{
			i++;
			multi_command[i] = strtok(NULL, "||");
		}
		multi_command[i] = NULL;
		return (0);
	}
	linker = _strstr(buffer, "&&");
	if (linker)
	{
		multi_command[i] = strtok(buffer, "&&");
		while (multi_command[i] != NULL)
		{
			i++;
			multi_command[i] = strtok(NULL, "&&");
		}
		multi_command[i] = NULL;
		return (1);
	}
	return (0);
}