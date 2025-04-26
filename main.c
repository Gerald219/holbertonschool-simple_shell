#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *input = NULL;
	size_t size = 0;

	while (1)
	{
		printf("$ ");

		if (getline(&input, &size, stdin) == -1)
		{
			free(input);
			exit(0);
		}

		printf("%s", input);
	}

	free(input);
	return(0);

}
