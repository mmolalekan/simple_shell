#ifndef SHELL_H
#define SHELL_H

/*Standard Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*EXTERNS*/
extern char **environ;

/*CORE*/
int execute(const char *pathname, char *const argv[], char *const env[]);

/*UTILS*/
int _putchar(char c);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
int _atoi(char *s);

/*MISCELLANEOUS*/
char **cpy_env(char **list);
char **tokenize(char **lineptr);

#endif
