# Competitive-programming setup — Geothermal

## Evidence date and scope

This setup is documented by the video published on 2021-05-30, its supplied
transcript, and the exact linked Pastebin files. It describes Jay's setup at
that time; it is not evidence of his current machine in 2026.

## Operating environment and terminal

- Windows Subsystem for Linux, using Ubuntu.
- WSLtty as the terminal emulator.
- Solarized Light as both the terminal and Vim color scheme.
- WSL files accessed from Windows through `\\wsl$\Ubuntu`.
- `g++` installed inside the Linux environment.
- `ulimit -s unlimited` placed in `.bashrc` to remove the local stack limit.
- `export PATH=$PATH:~/scripts/` placed in `.bashrc` so helper scripts can be
  invoked by name.

His stated reason for WSL was Unix tooling and substantially faster shell-based
stress testing than his previous Windows command-line script.

## Vim configuration

Exact file: `artifacts/dotfiles/vim/.vimrc`.

Core behavior:

- Four-space tabs and indentation, expanded to spaces.
- Automatic and smart indentation, line numbers, relative line numbers,
  incremental search, ruler, and visible partial commands.
- Solarized Light with 256 terminal colors.
- Vundle as plugin manager.
- Plugins: `vimtex` and `vim-cpp-enhanced-highlight` in addition to Vundle.
- SumatraPDF configured as VimTeX's viewer with reuse-instance options.
- `jk` leaves insert mode.
- Pressing Enter after `{` inserts a matching brace and opens an indented line.
- `Ctrl-A` selects the entire buffer.
- Bells are disabled.
- New `*.cpp` files read
  `/home/jayleeds/vimcp/Library/Template.cpp` automatically.
- `F9` writes and calls `build.sh` on the current filename stem.
- `F10` runs the resulting local executable.
- Yanks are copied to Windows through `/mnt/c/Windows/System32/clip.exe` when
  that executable exists.
- TeX buffers disable the cursor line and relative numbering, retain absolute
  numbers, and disable matchparen behavior.

The configuration contains hard-coded WSL, Linux-home, and SumatraPDF paths;
copying it to macOS or native Linux requires adaptation.

## C++ template

Exact file: `artifacts/templates/cpp/Template.cpp`.

The template uses C++17-era GNU contest conventions:

- `#pragma GCC optimize("O3")` and `#pragma GCC target("sse4")`.
- `<bits/stdc++.h>` and `using namespace std`.
- Short aliases for integer, floating-point, complex, pair, vector, and
  priority-queue types.
- Loop macros (`FOR`, `F0R`, reverse variants, and `trav`).
- Container macros/aliases such as `sz`, `all`, `pb`, `lb`, and `ub`.
- `ckmin` and `ckmax` helpers.
- A time-seeded `mt19937` and `uid(a,b)` random-integer macro.
- Constants `MOD`, `nl`, and `MX`.
- `solve()` plus a configurable test-case loop in `main()`.
- Fast iostream setup and `cin.exceptions(cin.failbit)`.

The `sse4` target and static build command are environment-specific; treat the
file as historical reference rather than a portable drop-in template.

## Build script

`build.sh A` compiles `A.cpp` to executable `A` using:

```text
g++ -static -DLOCAL -lm -s -x c++ -Wall -Wextra -O2 -std=c++17 -o A A.cpp
```

It enables a `LOCAL` preprocessor symbol, requests static linking, strips the
binary, uses optimization, and enables common warnings. It does not stop on
shell errors or quote the argument, so filenames are implicitly expected to be
simple contest stems.

## Stress testing

### `stress.sh solutionA solutionB generator numTests`

For each test it runs the generator into `input`, sends that input to both
solutions, and compares their output files with `cmp`. On a mismatch it prints
the input and both outputs and exits; otherwise it reports that all tests
passed. The script computes MD5 strings but does not use them—the decisive
comparison is `cmp -s`.

### `validate.sh solution validator generator numTests`

For each generated input it runs the solution, concatenates input and output,
feeds them to the validator, and accepts only when the validator result begins
with `OK`. On failure it prints the input, solution output, and validator
result.

### `interact.sh solution interactor numTests`

It copies `runner.py` from a hard-coded library path, uses the Python runner to
connect the solution and interactor bidirectionally, records the prefixed
conversation, and accepts only when the last non-empty line is exactly
`Int: OK`. The path to `runner.py` must be changed for another installation.

### `runner.py`

The runner launches two subprocesses with `asyncio`, pipes each program's
stdout into the other's stdin, mirrors both stdout streams with configurable
prefixes, and separately mirrors stderr. It is infrastructure for the
interactive-test wrapper, not a problem solution.

## What is not documented

- No GitHub-hosted solution archive or reusable algorithm library was found.
- No current post-2021 setup update was found.
- The video demonstrates generators and use of the scripts, but no separate
  generator template was linked in the description.
