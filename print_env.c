#include "shell.h"
#include <unistd.h>
#include <string.h>

/**
 * print_env - prints the current enviroment variables
 * @args: unused but keeping for compatibility
 *
 * Return: Always 1 to continue executing shell
 */
int print_env(char **args)
{
	int i = 0;

	(void)args;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (1);
}
