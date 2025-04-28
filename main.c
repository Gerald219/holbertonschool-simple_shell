#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * main - Entry point for simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
	char **args;
	size_t size = 0;
	ssize_t characters;

	while (1)
	{
		display_prompt();
		characters = getline(&input, &size, stdin);

		if (characters  == -1)
		{
			free(input);
			printf("\nExiting shell!\n");
			exit(0);
		}
		args = parser_input(input);
		if (args && args[0] && strcmp(args[0], "exit") == 0)
		{
			free(input);
			free(args);
			printf("\nExiting Shell!\n");
			exit(0);
		}
		executor(args);
	}
	free(input);
	return(0);
}
