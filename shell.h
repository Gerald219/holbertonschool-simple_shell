#ifndef SHELL_H
#define SHELL_H

/**
 * file: header file for simple shell
 * contents: function prototypes for shell
 */

void display_prompt(void);

char **parser_input(char *input);
void exit_shell(char **args);
int builtin_handler(char **args);
int print_env(char **args);

char **split_path(char *path_env);
char *build_path(char *folder, char *command);
char *find_full_path(char *command, char **path_dirs);

char *_getenv(const char *name);
void free_array(char **array);

#endif /* SHELL_H */
