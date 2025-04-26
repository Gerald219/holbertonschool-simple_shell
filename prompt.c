#include "shell.h"
#include <stdio.h>

/**
 * display_prompt - prints the shell prompt, so we can type
 */
void display_prompt(void)
{
	if (printf("$ ") < 0)
	{
		perror("Error printing prompt");
	}
}
