#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * exit_shell - clean up memory and exit the shell safely
 * @args: the input writen split into words (array of strings)
 */
void exit_shell(char **args)
{
	if (args != NULL)
	{
		int i = 0;

		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}

		free(args);
	}

	exit(EXIT_SUCCESS);
}
