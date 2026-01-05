# Minishell 🐚

A tiny interactive shell built for 42, powered by GNU Readline history, a handcrafted lexer/parser, and a custom execution engine.

## ✨ Highlights
- 💬 Readline prompt (`minishell➜`) with history and auto-completion.
- 🧠 Tokenizer & parser for pipes `|`, redirections `< > >> <<`, logical operators, quotes, `$VAR`/`$?` expansion, and grammar validation.
- 🚰 Heredoc handling with expansion rules, temp files, and signal-aware child processes.
- 🔁 Pipelines and per-command redirections (single & multi) with ambiguity checks.
- 🧩 Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- 🌱 Environment list bootstrap (`PWD`, `SHLVL`) and export/unset helpers.
- 🧹 Custom GC plus dynamic arrays/strings and linked lists to track allocations cleanly.
- 🔒 Signal handling: ignore `SIGQUIT`, friendly `SIGINT`, heredoc-specific traps.
- 🧪 Valgrind suppression for readline/history (`readline.supp`).

## 🗂️ Repository tour
- `minishell.c` - entry point, signal setup, readline loop, parser/executor hookup.
- `includes/` - public headers for tokens, parser, executor, data structures, GC.
- `parsing/` - lexer & expansion logic, grammar checks, heredoc helpers, pipeline builder.
- `execution/` - executor, pipeline/pipe helpers, redirection handlers.
- `lib/builtins/` - implementations of built-ins listed above.
- `lib/extra_cmd/` - path resolution & external command execution utilities.
- `lib/utils/` - GC, error helpers, command/file checks.
- `lib/data_structures/` - dynamic array/string and linked list primitives.
- `lib/bootstrap/` - environment initialization when `envp` is empty.
- `libft/` - 42 libc/printf/get_next_line base library used throughout.
- `Makefile` - builds `minishell` and links `-lreadline -lhistory`.

## 🛠️ Prerequisites
- GNU Readline headers/libs (`libreadline-dev` on Debian/Ubuntu, `brew install readline` on macOS).
- A POSIX toolchain (`cc`, `make`).
- Ensure `pkg-config` can find readline headers to avoid `readline/history.h` errors.

## 🏗️ Build & Run
```bash
make         # builds libft then minishell
make run     # build then launch the shell
./minishell  # run manually after building
```

### ▶️ Quick try
```bash
minishell➜ echo "hello" | cat > out.txt
minishell➜ cat <<EOF
heredoc line
EOF
minishell➜ export PATH=/usr/bin:$PATH && ls
minishell➜ exit
```

## 🧪 Debugging
Use the provided suppressions to quiet known readline leaks:
```bash
valgrind --suppressions=readline.supp ./minishell
```
