*This project has been created as part of the 42 curriculum by pedraza and plepercq*

# Minishell

[Subject](https://cdn.intra.42.fr/pdf/pdf/222781/en.subject.pdf)

## Description

**Minishell** is a simplified implementation of bash. The goal is to understand how a Unix shell works from the inside: reading user input, parsing commands, and executing them via system calls.

### Features

#### Command execution
- Execute any binary found in `PATH`
- Absolute and relative paths (`/bin/ls`, `./program`)
- Command arguments

#### Builtins
| Command | Description |
|---|---|
| `echo` | Print arguments (`-n` flag supported) |
| `cd` | Change current directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print environment |
| `exit` | Exit the shell |

#### Redirections / Heredoc
| Operator | Description |
|---|---|
| `<` | Redirect stdin from file |
| `>` | Redirect stdout to file (truncate) |
| `>>` | Redirect stdout to file (append) |
| `<<` | Heredoc — read until delimiter |

#### Pipes
- Chain commands with `|`
- Each command runs in its own child process

#### Environment variables
- Expand `$VAR` and `$?`
- Single quotes `'` — no expansion
- Double quotes `"` — expansion inside

#### Signals
| Signal | Key | Behavior |
|---|---|---|
| `SIGINT` | `Ctrl+C` | Interrupt current command, new prompt |
| `SIGQUIT` | `Ctrl+\` | Ignored at prompt, core dump in child |
| `EOF` | `Ctrl+D` | Exit shell |

### How it works

```
readline()
    │
    ▼
Tokeniser / Lexer  →  [ TOKEN_WORD ] [ TOKEN_PIPE ] [ TOKEN_REDIR ] ...
    │
    ▼
Parser  →  command list
    │
    ▼
Executor
    ├── builtin? → execute directly
    └── external? → fork() → execve()
```

---

## Instructions

### Usage

```bash
make            # Compilation
./minishell     # Execution
```

### Cleanup

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile from scratch
```




---

## Usage

```bash
make
./minishell
```

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

- Documentation on availables functions
- [Blog CodeQuoi](https://www.codequoi.com/pourquoi-je-necris-plus-darticles-sur-les-projets-de-42/#minishell)
- Videos on YouTube
- Friends ;)

### AI Usage

- **Debugging:** Used AI to understand error messages
- **Concepts:** Asked AI to assist me in project conception
- **No code generation:** All code was written and understood by me personally

## Authors

- **mpedraza** — [mpedraza@student.42.fr]
- **plepercq** — [plepercq@student.42.fr]
