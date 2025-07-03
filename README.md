# Minishell

Because a big one, is just too big.

Minishell is a 42 School project that challenges students to build their own Unix shell from the ground up. It's a command-line interpreter that bridges the gap between human language and machine code.

## Features

- **Command Execution**: Execute simple commands with arguments.
- **Pipes**: Chain multiple commands together using the `|` operator.
- **Redirections**:
  - Redirect input using `<`.
  - Redirect output using `>`.
  - Append output using `>>`.
  - Heredoc using `<<`.
- **Built-in Commands**:
  - `echo`: Display a line of text.
  - `cd`: Change the current directory.
  - `pwd`: Print the current working directory.
  - `export`: Set environment variables.
  - `unset`: Unset environment variables.
  - `env`: Display the environment.
  - `exit`: Exit the shell.
- **Signal Handling**: Handles `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.

## How it Works

The minishell works in three main stages: the lexer, the parser, and the executor.

### 1. Lexer

The lexer takes the raw input string and breaks it down into a series of tokens. Each token represents a meaningful unit, such as a command, an argument, a pipe, or a redirection. The lexer uses a state machine to handle different contexts, such as quoted strings and special characters.

### 2. Parser

The parser takes the list of tokens from the lexer and builds a command structure. This structure represents the relationships between commands, pipes, and redirections. The parser is responsible for ensuring that the command syntax is correct and for reporting any errors.

### 3. Executor

The executor takes the command structure from the parser and executes the commands. It creates child processes for each command, sets up pipes and redirections, and manages the execution of the commands.

## Commands

The following built-in commands are supported:

- `echo [-n] [string ...]`: Write arguments to the standard output. The `-n` option suppresses the trailing newline.
- `cd [directory]`: Change the current working directory.
- `pwd`: Print the current working directory.
- `export [name[=value] ...]`: Set environment variables.
- `unset [name ...]`: Unset environment variables.
- `env`: Print the environment.
- `exit [n]`: Exit the shell with a status of `n`.

## Getting Started

### Prerequisites

- A C compiler (e.g., `clang` or `gcc`)
- `make`
- `wget`
- `tar`
- `gzip`

### Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/cliftontoaster-reid/minishell.git
   cd minishell
   ```

2. Build the project:

   ```bash
   make
   ```

   This will create the `minishell` executable in the root directory.

### Running Minishell

To start the shell, run the following command:

```bash
./minishell
```

## Development

### Building for Debugging

To build the project with debugging symbols, use the following command:

```bash
make CFLAGS="-Wall -Wextra -Werror -g3"
```

### Running Tests

The project includes a suite of unit tests using the Criterion framework. To run the tests, use the following command:

```bash
make run_test
```

## Third-party Licenses

This project uses the following third-party libraries:

### Criterion Testing Framework

The Criterion testing framework is used for unit testing and is licensed under the MIT Licence.

Copyright © 2015-2017 Franklin "Snaipe" Mathieu <http://snai.pe/>

See `licenses/CRITERION-MIT-LICENSE` for the full license text.

Repository: [https://github.com/Snaipe/Criterion](https://github.com/Snaipe/Criterion)

### Libft

Libft is a custom C library that provides various utility functions. It is licensed under the MIT Licence.

Copyright © 2025 Clifton Toaster Reid

See `licenses/LIBFT-MIT-LICENSE` for the full licence text.

Repository: [seed.radicle.garden](https://app.radicle.xyz/nodes/seed.radicle.garden/rad:z2r3ahNug1N33eWu4iD7NiuphqUL3)
