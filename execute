#include "shell.h"

/**
 * execute - executes a command with arguments
 *
 * @command: the command to execute
 * @argv: an array of arguments
 * @env: an array of environment variables
 */
int execute(char *command, char *argv[], char *env[])
{
	pid_t pid;
	int status;

	/* Return if command is null or empty */
	if (command == NULL || *command == '\0')
		return 1;

	pid = fork();

	/* If fork failed */
	if (pid < 0)
	{
		write(2, "fork failed\n", 12);
		_exit(1);
	}
	
	/* Child process */
	else if (pid == 0)
	{
		/* Search for command in PATH */
		char *path = _getenv("PATH");
		char *path_copy = _strdup(path);
		char *dir = strtok(path_copy, ":");
		char *path_command = NULL;
		
		/* Execute command with absolute path */
		if (_strchr(command, '/') != NULL)
		{
			execve(command, argv, env);
			/* the remainder of this code shouldn't run if execve is successful. However, If execve fails, the following lines will run */
			write(2, command, _strlen(command));
			write(2, ": command not found\n", 20);
			_exit(1);
		}

		/* Execute command with relative path */
		while (dir != NULL)
		{
			path_command = malloc(_strlen(dir) + _strlen(command) + 2);
			_strcpy(path_command, dir);
			_strcat(path_command, "/");
			_strcat(path_command, command);
			execve(path_command, argv, env);
			free(path_command);
			dir = strtok(NULL, ":");
		}

		/* If command was not found in PATH */
		write(2, command, _strlen(command));
		write(2, ": command not found\n", 20);
		_exit(1);
	}
	/* Parent process */
	else
		waitpid(pid, &status, 0);
	return 0;
}
