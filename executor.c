#include "shell.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
 * executor - Run a command in a child without replacing the shell
 * @args: Tokenized input command
 * Return: Command exit status, or 126/127 on execution failure
 */
int executor(char **args)
{
	pid_t child_pid;
	int status, error;
	char *full_path;
	char **path_dirs;

	if (!args || !args[0])
		return (0);
	if (strchr(args[0], '/'))
		full_path = strdup(args[0]);
	else
	{
		path_dirs = split_path(_getenv("PATH"));
		full_path = find_full_path(args[0], path_dirs);
		free_array(path_dirs);
	}
	if (!full_path)
	{
		fprintf(stderr, "hsh: %s: not found\n", args[0]);
		return (127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(full_path);
		return (1);
	}
	if (child_pid == 0)
	{
		execve(full_path, args, environ);
		error = errno;
		perror(args[0]);
		free(full_path);
		_exit(error == ENOENT ? 127 : 126);
	}
	free(full_path);
	while (waitpid(child_pid, &status, 0) == -1)
	{
		if (errno != EINTR)
		{
			perror("waitpid");
			return (1);
		}
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (128 + WTERMSIG(status));
}
