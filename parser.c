#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parser_input - splits the string into seperate words
 * @input: the full string or typed data from user
 * Return: array of words
 */
char **parser_input(char *input)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 64);
	if (args == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, " \n");
	while (token != NULL)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}

	args[i] = NULL;

	return (args);
}
