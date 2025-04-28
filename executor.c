#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

/**
 * executor - Run a command in a child process
 * @args: Tokenized input command
 */
void executor(char **args)
{
	pid_t child_pid;
	int status;
	char *full_path;

	if (!args || !args[0])
		return;

	full_path = find_full_path(args[0]);
	if (!full_path)
	{
		perror("./hsh");
		return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(full_path);
		return;
	}

	if (child_pid == 0)
		execve(full_path, args, environ);
	else
		waitpid(child_pid, &status, 0);

	free(full_path);
}
