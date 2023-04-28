#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to be converted
 *
 * Return: the int converted from the string
 */
int _atoi(char *s)
{
int i, d, n, len, f, digit;

i = 0;
d = 0;
n = 0;
len = 0;
f = 0;
digit = 0;

while (s[len] != '\0')
len++;

while (i < len && f == 0)
{
if (s[i] == '-')
++d;

if (s[i] >= '0' && s[i] <= '9')
{
digit = s[i] - '0';
if (d % 2)
digit = -digit;
n = n * 10 + digit;
f = 1;
if (s[i + 1] < '0' || s[i + 1] > '9')
break;
f = 0;
}
i++;
}

if (f == 0)
return (0);

return (n);
}

/**
 * _itoa - convert integer to string
 *
 * @num: Number to convert
 * @str: array to store converted int
 * @radix: Base of conversion
 */

void _itoa(int num, char *str, int radix)
{
	int i = 0;

	if (num == 0)
	{
		str[i] = '0';
		i++;
		str[i] = '\0';
	}
	while (num != 0)
	{
		int remainder = num % radix;
		
		str[i] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
		i++;
		num /= radix;
	}
	str[i] = '\0';
	rev_string(str);
}

/**
 * rev_string - return string reversed
 * @s: pointer
 */

void rev_string(char *s)
{
char rev = s[0];
int counter = 0;
int i;

while (s[counter] != '\0')
counter++;
for (i = 0; i < counter; i++)
{
counter--;
rev = s[i];
s[i] = s[counter];
s[counter] = rev;
}
}
