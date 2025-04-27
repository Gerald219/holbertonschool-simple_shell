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

#endif /* SHELL_H */
