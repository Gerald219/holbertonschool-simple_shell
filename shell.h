#ifndef SHELL_H
#define SHELL_H

/**
 * file: header file for simple shell
 * contents: function prototypes for shell
 */

void display_prompt(void);


void exit_shell(char **args);
int builtin_handler(char **args);
int print_env(char **args);



char *_getenv(const char *name);
void free_array(char **array);

#endif /* SHELL_H */
