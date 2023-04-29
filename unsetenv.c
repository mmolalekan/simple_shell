/**
 * unsetenv - remove a variable from the environment
 * @name: the name of the variable to remove
 *
 * Return: 0 on success, or -1 on failure
 */
int unsetenv(const char *name)
{
	int i, j, len;
	extern char **environ;

	if (!name || !*name || _strchr(name, '='))
	{
		errno = EINVAL;
		return (-1);
	}

	len = _strlen(name);
	for (i = 0; environ[i]; i++)
	{
		if (!_strncmp(environ[i], name, len) && environ[i][len] == '=')
		{
			for (j = i; environ[j]; j++)
			{
				environ[j] = environ[j + 1];
			}
			break;
		}
	}

	return (0);
}

