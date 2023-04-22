#ifndef SHELL_H
#define SHELL_H

/*Standard Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/*EXTERNS*/
extern char **environ;

/*CORE*/
int execute(char *command, char *argv[], char *env[]);

/* UTILS */
int _putchar(char c);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
int _atoi(char *s);
char *_strdup(char *str);
char *_getenv(const char *name);
char *_strchr(char *s, char c);
char *_strstr(char *haystack, char *needle);


/* MISCELLANEOUS */
char **cpy_env(char **list);
char **tokenize(char **lineptr);

#endif
