int main(int argc, char **argv)
{
	if (argc != 2)
	{
		const char *msg = "Usage: ";
		const char *cmd = argv[0];
		const char *arg = " status\n";
		size_t len = _strlen(msg) + _strlen(cmd) + _strlen(arg) + 1;
		char usage_msg[len];

		strcpy(usage_msg, msg);
		strcat(usage_msg, cmd);
		strcat(usage_msg, arg);
		write(STDERR_FILENO, usage_msg, len);
		return (1);
	}
	int status = _atoi(argv[1]);

	exit(status);
}
