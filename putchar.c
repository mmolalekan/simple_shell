#include "shell.h"

/**
 * _putchar - Print character to console
 *
 * @c: Character to print
 * Return: int
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}
