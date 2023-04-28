#include "shell.h"

/**
 *_memcpy - a function that copies memory area
 *@dest: memory where is stored
 *@src: memory where is copied
 *@n: number of bytes
 *
 *Return: copied memory with n byted changed
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	int r = 0;
	int i = n;

	for (; r < i; r++)
	{
		dest[r] = src[r];
		n--;
	}
	return (dest);
}

/**
 * _memmove - moves memory location
 *
 * @dest: destination
 * @src: source
 * @n: Number of bytes to move
 * Return: void*
 */

void *_memmove(void *dest, const void *src, size_t n)
{
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *) src;
	size_t i;

	if (dest_ptr <= src_ptr)
	{
		for (i = 0; i < n; i++)
		{
			dest_ptr[i] = src_ptr[i];
		}
	}
	else
	{
		for (i = n; i > 0; i--)
		{
			dest_ptr[i - 1] = src_ptr[i - 1];
		}
	}
	return (dest);
}
