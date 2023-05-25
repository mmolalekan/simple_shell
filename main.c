#include "shell.h"

/**
 * hsh - shell loop
 * @info: info struct
 * @av: argument vector list
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_result = 0;

	while (r != -1 && builtin_result != -2)
	{
		init_data(info);
		if (_isatty(info))
			_puts("$ ");
		_errputchar(BUFF_FLUSH);
		r = getinput(info);
		if (r != -1)
		{
			set_data(info, av);
			builtin_result = check_builtin(info);
			if (builtin_result == -1)
				run_cmd(info);
		}
		else if (_isatty(info))
			_putchar('\n');
		free_data_mem(info, 0);
	}
	write_history(info);
	free_data_mem(info, 1);
	if (!_isatty(info) && info->status)
		exit(info->status);
	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_result);
}

/**
 * check_builtin - checks for builtin commands
 * @info: info struct
 *
 * Return: -1 - builtin not found,
 *			0 - builtin executed successfully,
 *			1 - builtin found but not successful,
 *			-2 - builtin signals exit()
 */
int check_builtin(data_t *info)
{
	int i, built_in_result = -1;

	builtin_t builtintbl[] = {
		{"exit", e_exit},
		{"env", _env},
		{"help", _help},
		{"history", _history},
		{"setenv", call_setenv},
		{"unsetenv", call_unsetenv},
		{"cd", cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[i].func(info);
			break;
		}
	return (built_in_result);
}

/**
 * run_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void run_cmd(data_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->line_count++;
		info->lc_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		_fork(info);
	}
	else
	{
		if ((_isatty(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * _fork - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void _fork(data_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_data_mem(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	data_t info[] = { INIT_DATA };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_errputs(av[0]);
				_errputs(": 0: Can't open ");
				_errputs(av[1]);
				_errputchar('\n');
				_errputchar(BUFF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = fd;
	}
	make_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
