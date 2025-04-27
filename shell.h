#ifndef SHELL_H
#define SHELL_H

/**
 * file: header file for simple shell
 * contents: function prototypes for shell
 */

void display_prompt(void);
char **parser_input(char *intput);
void executor(char **args);
void exit_shell(char **args);
int vuiltin_handler(char **args);
int print_env(char **args);
char *build_path(char *dir, char *cmd);
char *find_full_path(char *command, char **path_dirs);

#endif /* SHELL_H */
