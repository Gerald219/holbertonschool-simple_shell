#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - Entry point for simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *input = NULL;
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

		printf("%s", input);
	}

	free(input);
	return(0);

}
