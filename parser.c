#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * parser_input - Split input string into arguments (tokens)
 * @input: Full input line entered by user
 *
 * Return: Array of words (tokens) or NULL if fail
 */
char **parser_input(char *input)
{
	char **args, **grown;
	char *token;
	size_t i = 0, capacity = 16;

	if (!input)
		return (NULL);

	args = malloc(sizeof(char *) * capacity);
	if (!args)
		return (NULL);

	token = strtok(input, " \t\r\n");
	while (token != NULL)
	{
		if (i + 1 == capacity)
		{
			capacity *= 2;
			grown = realloc(args, sizeof(char *) * capacity);
			if (!grown)
			{
				free(args);
				return (NULL);
			}
			args = grown;
		}
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	return (args);
}
