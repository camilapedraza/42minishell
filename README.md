*This project has been created as part of the 42 curriculum by pedraza and plepercq*

# So Long

[Subject](https://cdn.intra.42.fr/pdf/pdf/222781/en.subject.pdf)

## Description

**Minishell** is a simplified implementation of bash. The goal is to understand how a Unix shell works from the inside: reading user input, parsing commands, and executing them via system calls.


### Features

We had to implement the following builtins commands. 
- cd : to move in the file system
- echo : to echo in the terminal the follozing text given as argument
- env : display or use env variables
- exit : exit program execution
- export : define and display new env variables
- pwd : display current path directory in fyle system
- unset : remove given vars from env variables

## Instructions

### Compilation

```bash
make
```

This will compile the project and produce the `minishell` executable.

### Usage

```bash
./minishell
```

### Cleanup

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile from scratch
```

---

## Resources

### Documentation & References

- [Doc]()

### AI Usage

- **Debugging:** Used AI to understand error messages
- **Concepts:** Asked AI to assist me in project conception
- **No code generation:** All code was written and understood by me personally






















# Minishell

> A minimal Unix shell written in C — École 42 project

---

## Overview

Minishell is a simplified implementation of bash. The goal is to understand how a Unix shell works from the inside: reading user input, parsing commands, and executing them via system calls.

---

## Features

### Command execution
- Execute any binary found in `PATH`
- Absolute and relative paths (`/bin/ls`, `./program`)
- Command arguments

### Builtins
| Command | Description |
|---|---|
| `echo` | Print arguments (`-n` flag supported) |
| `cd` | Change current directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print environment |
| `exit` | Exit the shell |

### Redirections
| Operator | Description |
|---|---|
| `<` | Redirect stdin from file |
| `>` | Redirect stdout to file (truncate) |
| `>>` | Redirect stdout to file (append) |
| `<<` | Heredoc — read until delimiter |

### Pipes
- Chain commands with `\|`
- Each command runs in its own child process

### Environment variables
- Expand `$VAR` and `$?`
- Single quotes `'` — no expansion
- Double quotes `"` — expansion inside

### Signals
| Signal | Key | Behavior |
|---|---|---|
| `SIGINT` | `Ctrl+C` | Interrupt current command, new prompt |
| `SIGQUIT` | `Ctrl+\` | Ignored at prompt, core dump in child |
| `EOF` | `Ctrl+D` | Exit shell |

---

## Architecture

```
minishell
├── Lexer        — tokenize raw input into a list of tokens
├── Parser       — build a command structure from tokens
├── Executor     — fork/execve commands, handle pipes & redirections
├── Builtins     — internal commands executed without fork
├── Environment  — linked list of key/value pairs
└── Signals      — context-aware signal handling (MAIN/CHILD/WAIT/CONTINUED)
```

---

## How it works

```
readline()
    │
    ▼
Lexer  →  [ TOKEN_WORD ] [ TOKEN_PIPE ] [ TOKEN_REDIR ] ...
    │
    ▼
Parser  →  command list / AST
    │
    ▼
Executor
    ├── builtin? → execute directly
    └── external? → fork() → execve()
```

---

## Usage

```bash
make
./minishell
```

---

## Requirements

- `gcc`, `make`
- `readline` library (`libreadline-dev`)

```bash
sudo apt install libreadline-dev
```

Compile with :
```bash
gcc -Wall -Wextra -Werror -lreadline
```

---

## Norminette

All source files comply with the **42 Norm** coding standard.

---

## Authors

- **mpedraza** — [mpedraza@student.42.fr](mailto:mpedraza@student.42.fr)