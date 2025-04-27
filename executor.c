#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * executor - creates a child process to execute commands
 * @args: array of parse command arguments
 */
void executor(char **args)
{
	pid_t pid;

	if (args == NULL || args[0] == NULL)
		return;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return;
	}
	if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
