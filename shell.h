#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct string_list - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct string_list
{
	int num;
	char *str;
	struct string_list *next;
} list_t;

/**
 *struct info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@lc_flag: if on count this line of input
 *@filename: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@new_env: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buff, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line input
 *@history_count: the history line number count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int lc_flag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int new_env;
	int status;

	char **cmd_buff;
	int cmd_buff_type;
	int read_fd;
	int history_count;
} data_t;

#define INIT_DATA \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_t;


/* loop */
int hsh(data_t *, char **);
int check_builtin(data_t *);
void run_cmd(data_t *);
void _fork(data_t *);
int loop(char **);

/* parser */
int is_command(data_t *, char *);
char *duplicate_char(char *, int, int);
char *search_path(data_t *, char *, char *);
int is_chain(data_t *, char *, size_t *);
void check_chain(data_t *, char *, size_t *, size_t, size_t);
int modify_alias(data_t *);
int modify_vars(data_t *);
int modify_string(char **, char *);
int _isatty(data_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors */
void _errputs(char *);
int _errputchar(char);
int _putcfd(char c, int fd);
int _putsfd(char *str, int fd);
int _erratoi(char *);
void print_err(data_t *, char *);
int print_int(int, int);
char *convert_number(long int, int, int);
void comment_handler(char *);

/* string functions */
int _strlen(char *);
int _strcmp(char *, char *);
char *initial(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **_strtok(char *, char *);
char **_strtok_r(char *, char);
ssize_t getinput(data_t *);
int _getline(data_t *, char **, size_t *);
void sigintHandler(int);

/* memory management functions */
char *_memset(char *, char, unsigned int);
void free_func(char **);
void *_realloc(void *, unsigned int, unsigned int);
int free_buff(void **);

/* builtin functions */
int e_exit(data_t *);
int cd(data_t *);
int _help(data_t *);
int _alias(data_t *);
void init_data(data_t *);
void set_data(data_t *, char **);
void free_data_mem(data_t *, int);

/* environ handlers */
char *_getenv(data_t *, const char *);
int _env(data_t *);
int call_setenv(data_t *);
int call_unsetenv(data_t *);
int make_env_list(data_t *);
char **get_environ(data_t *);
int _unsetenv(data_t *, char *);
int _setenv(data_t *, char *, char *);

/* history */
char *get_data_history(data_t *info);
int write_history(data_t *info);
int read_history(data_t *info);
int make_history_list(data_t *info, char *buf, int linecount);
int adjust_history_list(data_t *info);
int _history(data_t *);

/* linked list */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t print_string_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_initial(list_t *, char *, char);
ssize_t get_node_at_index(list_t *, list_t *);

#endif
