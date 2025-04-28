# Simple Shell Project 2025 

This project is a basic Unix command line interpreter (shell), a mini terminal, written with C language. It reads commands typed by the use, executes them and displays the content to screen.

## How to Compile
'''python

The following command:

### gcc -Wall -Werror -Wextra -pedantic -stdgnu89 *.c -o hsh

### -Wall = Enable all warnings.
### -Werror = Treat Warnings as errors.
### -Wextra = Enable extra warnings.
### -pedantic = Enforce strict ISO C compliance.
### -std+gnu89 = use the OLD version GNU89 C Standard.

## How to Run: 

To run the Simple Shell:

1. Open your terminal.
2. Compile the program if you haven't already:
`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`
3. Start the shell by running:
`./hsh`
4. You will see a prompt (`$`) waiting for your commands.

Example:

$ /bin/ls
(build_path.c, executor.c, find_full_path.c, main.c, etc.)
To exit the shell, type:
$ exit
