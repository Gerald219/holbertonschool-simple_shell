#include "shell.h"
#include <string.h>

/**
 * builtin_handler - handles commands like exit & env
 * @args: array of command arguments (string split into words)
 *
 * Return: 1 if a built-in command was executed, 0 if not built-in
 */
int builtin_handler(char **args)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		exit_shell(args);
		return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_env(args);
		return (1);
	}

	return (0);
}
