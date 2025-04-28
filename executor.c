#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * executor - Run a command in a child process
 * @args: Tokenized input command
 */
void executor(char **args)
{
	pid_t child_pid;
	int status;
	char *full_path;
	char **path_dirs;

	if (!args || !args[0])
		return;
	if (args[0][0] == '/')
	{
		execve(args[0], args, environ);
		perror("./hsh");
		exit(EXIT_FAILURE);
	}

	path_dirs = split_path(_getenv("PATH"));
	full_path = find_full_path(args[0], path_dirs);
	if (args[0][0] == '/')
	{
		execve(args[0], args, environ);
	}

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
