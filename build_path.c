#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * build_path - creates a path by joining a directory and a command
 * @dir: directory path
 * @cmd: command name
 * Return: full path string or NULL if malloc fails
 */
char *build_path(char *dir, char *cmd)
{
	char *full_path;
	int len_dir, len_cmd;

	len_dir = strlen(dir);
	len_cmd = strlen(cmd);

	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
		return (NULL);

	strcpy(full_path, dir);
	strcat(full_path, "/");
	strcat(full_path, cmd);

	return (full_path);
}
