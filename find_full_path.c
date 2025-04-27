#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * find_full_path - find the full path of a command by checking each path directory
 * @command: command to find
 * @path_dirs: arrayof PATH directories
 *
 * Return: full path sting or NULLif not found
 */
char *find_ful_path(char *command, char **path_dirs)
{
	char *full_path;
	int i = 0;

	while (path_dirs[i])
	{
		full_path = build_path(path_dirs[i], command);
		if (!full_path)
			return (NULL);

		if (access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);
		i++;
	}
	return (NULL);
}
