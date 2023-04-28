#include <stdio.h>
#include <string.h>

/* function prototype */
char *_strtok(char *str, const char *delim);

int main(void)
{
    char str[] = "Hello, world! How are you today?";
    const char delim[] = " ,!"; /* delimiters are space, comma, and exclamation mark */
    char *token;

    /* get the first token */
    token = _strtok(str, delim);

    /* walk through other tokens */
    while (token != NULL)
    {
        printf("%s\n", token);
        token = _strtok(NULL, delim);
    }

    return 0;
}

