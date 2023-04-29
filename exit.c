#include "shell.h"

/**
 * e_exit - Performs cleanup and exits the shell
 *
 * @status: exit status
 * @buffer: mem alloc'd
 */

void e_exit(int status, char *buffer)
{
	free(buffer);
	exit(status);
}
