#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * main - Entry point for simple shell
 *
 * Return: Status of the last command
 */
int main(void)
{
	char *input = NULL;
	char **args;
	size_t size = 0;
	ssize_t characters;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();
		characters = getline(&input, &size, stdin);

		if (characters  == -1)
			break;
		args = parser_input(input);
		if (!args)
		{
			perror("malloc");
			status = 1;
			break;
		}
		if (args && args[0] && strcmp(args[0], "exit") == 0)
		{
			free(args);
			break;
		}
		if (args[0])
		{
			if (builtin_handler(args))
				status = 0;
			else
				status = executor(args);
		}
		free(args);
	}
	free(input);
	return (status);
}
