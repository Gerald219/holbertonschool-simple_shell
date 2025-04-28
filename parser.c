#include "shell.h" /* Include header with prototypes */
#include <stdlib.h> /* For malloc and free */
#include <string.h> /* For strtok */

/**
 * parser_input - Split input string into arguments (tokens)
 * @input: Full input line entered by user
 *
 * Return: Array of words (tokens) or NULL if fail
 */
char **parser_input(char *input)
{
	char **args;
	char *token;
	int i = 0;

	if (!input)
		return (NULL);

	args = malloc(sizeof(char *) * 64);
	if (!args)
		return (NULL);

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
