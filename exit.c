#include "shell.h"

/**
 * e_exit - Performs cleanup and exits the shell
 *
 * @status: exit status
 * @buffer: mem alloc'd
 */

void e_exit(int status, char *buffer)
{
	if (isatty(STDIN_FILENO))
	free(buffer);
	exit(status);
}
