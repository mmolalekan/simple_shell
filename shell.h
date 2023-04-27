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
int execute(const char *pathname, char *const argv[], char *const env[]);

/* UTILS */
int _putchar(char c);
int _strlen(char const *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char const *src);
int _atoi(char *s);
char *_strdup(char *str);
char *_getenv(const char *name);
char *_strchr(char *s, char c);
char *_strstr(char *haystack, char *needle);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_memcpy(char *dest, char *src, unsigned int n);

/* MISCELLANEOUS */
char **tokenize(char *lineptr, char *delim);
char *search_path(char const *str);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void handle_rl_path(const char *p_name, char *const argv[], char *const env[]);

#endif
