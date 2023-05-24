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
	const char *src_ptr = (const char *)src;
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

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

/**
 * _memset - Fill memory with constant bytes
 *
 * @s: Pointer to memory
 * @b: byte to fill with
 * @n: number of byte to fill
 * Return:char*
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to the old block name.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	p = malloc(new_size);
	if (!p)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
