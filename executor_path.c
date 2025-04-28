#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * split_path - Splits the PATH environment variable into folders
 * @path_env: The PATH variable
 *
 * Return: Array of folder strings or NULL
 */
char **split_path(char *path_env)
{
    char **folders;
    char *path_copy, *token;
    int i = 0;

    if (!path_env)
        return (NULL);

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    folders = malloc(sizeof(char *) * 64);
    if (!folders)
    {
        free(path_copy);
        return (NULL);
    }

    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        folders[i] = strdup(token);
        if (!folders[i])
        {
            free(path_copy);
            return (NULL);
        }
        token = strtok(NULL, ":");
        i++;
    }
    folders[i] = NULL;
    free(path_copy);
    return (folders);
}

/**
 * build_path - Build a full path string
 * @folder: Folder name
 * @command: Command name
 *
 * Return: Full path string
 */
char *build_path(char *folder, char *command)
{
    char *full_path;
    int len;

    len = strlen(folder) + strlen(command) + 2;
    full_path = malloc(sizeof(char) * len);
    if (!full_path)
        return (NULL);

    strcpy(full_path, folder);
    strcat(full_path, "/");
    strcat(full_path, command);

    return (full_path);
}

/**
 * find_full_path - Search for the command in PATH directories
 * @command: The command name
 * @path_dirs: Array of folders from PATH
 *
 * Return: Full path if found or NULL
 */
char *find_full_path(char *command, char **path_dirs)
{
    struct stat st;
    char *full_path;
    int i = 0;

    path_dirs = split_path(getenv("PATH"));

    if (!command || !path_dirs)
        return (NULL);

    while (path_dirs[i])
    {
        full_path = build_path(path_dirs[i], command);
        if (!full_path)
            return (NULL);

        if (stat(full_path, &st) == 0)
            return (full_path);

        free(full_path);
        i++;
    }

    return (NULL);
}
