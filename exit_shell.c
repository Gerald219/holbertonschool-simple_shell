#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * exit_shell - clean up memory and exit the shell safely
 * @args: the input writen split into words (array of strings)
 */
void exit_shell(char **args)
{
	/* Tokens point into the input buffer and must not be freed individually. */
	free(args);

	exit(EXIT_SUCCESS);
}
