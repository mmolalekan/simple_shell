#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
/**
* main - test run the -getline funtion
* Return: 0 on success
*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("Enter some text:\n");
	nread = _getline(&line, &len, stdin);
	if (nread == -1)
	{
		perror("_getline");
		exit(1);
	}
	printf("You entered: %s", line);

	free(line);
	return (0);
}

