# Simple Shell Project 2025 

This project is a basic Unix command line interpreter 'shell', a mini terminal, written with 'C language'. It reads commands typed by the use, executes them and displays the content to screen.

## How to Compile

The following command:

### gcc -Wall -Werror -Wextra -pedantic -stdgnu89 *.c -o hsh

* -Wall = Enable all warnings.
* -Werror = Treat Warnings as errors.
* -Wextra = Enable extra warnings.
* -pedantic = Enforce strict ISO C compliance.
* -std+gnu89 = use the OLD version GNU89 C Standard.

## How to Run

To run the Simple Shell:

1. Open your terminal.
2. Compile the program if you haven't already:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
3. Start the shell by running:
`./hsh`
4. You will see a prompt (`$`) waiting for your commands.

### Example

$ /bin/ls
(build_path.c, executor.c, find_full_path.c, main.c, etc.)
To exit the shell, type:
$ exit

## FILES
** This Shell terminal is organized in multiple files. 

- `main.c` — Handles program start, prompt loop.

- `prompt.c` — Displays the shell prompt.

- `parser.c` — Parses user input into command arguments.

- `executor_path.c` — Handles command execution and path resolution.

- `exit_shell.c` — Manages built-in `exit` command.

- `builtin_handler.c` — Manages built-in `env` command.

- `print_env.c` — Prints environment variables.

- `shell.h` — Header file with prototypes and shared libraries.


## FEATURES OF THIS SHELL

✔️  Displays a custom prompt ($)

✔️  Reads user input

✔️  Tokenizes (splits) input

✔️  Executes commands like /bin/ls

✔️  Handles PATH resolution

✔️  Runs commands with or without /bin/

✔️  Handles exit command (exit cleanly)

✔️  Handles env command (prints environment variables)

✔️  Handles simple errors (command not found)

✔️  Gracefully handles Ctrl+D (EOF)


## Requirements

- Compiled on Ubuntu 20.04 LTS

- Using gcc 9.3.0 and flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`

- Code style fully compliant with Betty

- No memory leaks (Valgrind tested)

- Max 5 functions per .c file

- Header files properly include-guarded

- Only necessary system calls used

- Shell behaves like `/bin/sh` for command execution and error handling
