#include "shell.h"
#include <stddef.h>
#include <string.h>

extern char **environ;

/**
 * _getenv - custom implementation of getenv
 * @name: name of the environment variable to find
 * Return: pointer to value string or NULL if not found
 */
char *_getenv(const char *name)
{
    int i;
    size_t len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return (environ[i] + len + 1);
    }
    return (NULL);
}
