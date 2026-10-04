# Simple shell in C

A Holberton School coursework project: a small Unix command interpreter written in C. It demonstrates input parsing, dynamic allocation, environment variables, PATH lookup, and process creation with `fork`, `execve`, and `waitpid`.

## Build and run

Requirements: Linux/POSIX environment, GCC, and Make. Python 3 is needed for the regression tests.

```bash
make
./hsh
```

Or compile directly:

```bash
gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh
```

Interactive example:

```text
$ /bin/echo hello
hello
$ echo world
world
$ exit
```

Commands also work through standard input:

```bash
printf '/bin/echo first\necho second\n' | ./hsh
```

This prints `first` and `second` on separate lines, without an interactive prompt.

## Supported behavior

- Commands with absolute paths, relative paths, or PATH lookup.
- Whitespace-separated arguments and blank input lines.
- `env` to print environment variables, `exit` to leave the shell, and EOF to finish input.
- Child exit status propagation; 127 for missing commands and 126 for direct execution failures.
- Continued command processing after an execution failure.

This is a learning project, not a full POSIX shell. It does not implement quoting, pipes, redirection, variable expansion, job control, or numeric arguments to `exit`.

## Checks

```bash
make test
```

The process-level tests cover multiple commands, PATH resolution, relative execution, more than 64 arguments and PATH entries, built-ins, quiet EOF, and recovery from execution failures. GitHub Actions runs the same checks on pushes and pull requests.

## Source guide

| File | Responsibility |
| --- | --- |
| `main.c` | Read commands, dispatch built-ins, and release input memory |
| `parser.c` | Split input into arguments with a growing pointer array |
| `executor.c` | Fork a child, execute the command, and collect its status |
| `executor_path.c` | Split PATH, find executables, and free owned path strings |
| `_getenv.c` | Look up environment values |
| `builtin_handler.c`, `print_env.c`, `exit_shell.c` | Basic built-in handling |
| `prompt.c`, `shell.h` | Interactive prompt and shared declarations |

Argument tokens borrow memory from the input buffer; PATH entries own their allocated strings. Generated binaries and editor backups are excluded from version control.

## Author

[Gerald Mulero (@Gerald219)](https://github.com/Gerald219). See `AUTHORS` for the original contributor attribution.
