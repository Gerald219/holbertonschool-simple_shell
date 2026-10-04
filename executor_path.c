#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * free_array - Release an array of separately allocated strings
 * @array: NULL-terminated array
 */
void free_array(char **array)
{
	size_t i;

	if (!array)
		return;
	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

/**
 * split_path - Split PATH, preserving empty entries as the current directory
 * @path_env: PATH value
 * Return: Owned folder array or NULL
 */
char **split_path(char *path_env)
{
	char **folders;
	const char *start, *end, *cursor;
	size_t count = 1, i = 0, len;

	if (!path_env)
		return (NULL);
	for (cursor = path_env; *cursor; cursor++)
		if (*cursor == ':')
			count++;
	folders = calloc(count + 1, sizeof(char *));
	if (!folders)
		return (NULL);
	start = path_env;
	do {
		end = strchr(start, ':');
		len = end ? (size_t)(end - start) : strlen(start);
		folders[i] = len ? strndup(start, len) : strdup(".");
		if (!folders[i++])
		{
			free_array(folders);
			return (NULL);
		}
		if (end)
			start = end + 1;
	} while (end);
	return (folders);
}

/**
 * build_path - Build a full path string
 * @folder: Folder name
 * @command: Command name
 * Return: Owned path or NULL
 */
char *build_path(char *folder, char *command)
{
	char *full_path;
	size_t len = strlen(folder) + strlen(command) + 2;

	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	strcpy(full_path, folder);
	strcat(full_path, "/");
	strcat(full_path, command);
	return (full_path);
}

/**
 * find_full_path - Find an executable regular file in the supplied folders
 * @command: Command name
 * @path_dirs: Folder array
 * Return: Owned path or NULL
 */
char *find_full_path(char *command, char **path_dirs)
{
	struct stat st;
	char *full_path;
	size_t i;

	if (!command || !path_dirs)
		return (NULL);
	for (i = 0; path_dirs[i]; i++)
	{
		full_path = build_path(path_dirs[i], command);
		if (!full_path)
			return (NULL);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) &&
			access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	return (NULL);
}
