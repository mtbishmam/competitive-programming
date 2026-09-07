# Competitive-programming setup — ecnerwala

## Evidence timeline

Andrew's public evidence spans multiple eras and should not be blended into one
undated setup:

| Era | Strongest evidence | Meaning |
|---|---|---|
| 2015 | `cptemp` repository | Minimal C++11 template and Makefile workflow |
| ICPC book era | `icpc-book/content/contest/` | Portable team-reference setup, including a plugin-free Vim config |
| 2020 | Codeforces AMA and Kick Start Round E showcase | Vim/Neovim, YouCompleteMe, Makefile, and live contest workflow |
| 2026 snapshot | `dotfiles` and `cp-book` | Current published Neovim config, C++23 library, and contest tooling |

Repository state is evidence of published configuration, not proof that every
line is active on his live machine.

## Current published editor configuration (2026 snapshot)

The current editor file is
`sources/github/repos/dotfiles/vim/.config/nvim/init.lua`. His shell aliases
`vim` to `/usr/bin/nvim`, retains `/usr/bin/vim` as `oldvim`, and sets
`EDITOR=nvim`.

Core editing behavior:

- Four-column tabs and indentation, with real tabs (`expandtab=false`).
- Absolute line numbers, ruler, partial-command display, persistent undo,
  mouse support, visible whitespace, and right/below splits.
- C-family indentation with custom `cinoptions`.
- Case-insensitive search unless the pattern contains uppercase letters.
- `*` and `#` are remapped to whole-word searches that obey smart case.
- Enter clears search highlighting outside quickfix windows.
- `gA` yanks the whole buffer to the `+` clipboard.
- Files are checked for external changes when a buffer is entered or focus is
  regained.

The configuration uses Neovim's built-in package facility (`vim.pack.add`) and
loads:

- Navigation/UI: bclose, NERDTree, vim-airline, airline themes,
  vim-bufferline, and Solarized8.
- Editing/search/version control: delimitMate, NERDCommenter, vim-sleuth,
  vim-gitgutter, fzf/fzf.vim, and vim-fugitive.
- Language tooling: nvim-lspconfig, nvim-treesitter, VimTeX, vim-pandoc,
  Python indentation, JSX syntax, Circom syntax, and SimpylFold.
- Notes: workflowish.

GitHub Copilot and Codeium entries are present but commented out; they are not
evidence of active use.

Completion uses Neovim's native completion with omnifunc followed by up to five
current-buffer matches. LSP completion is enabled when supported. Configured
language servers are clangd, TypeScript, Pyright, gopls, Solidity, Rust,
Kotlin, and associated custom root/settings logic. Treesitter is attempted for
all file types and drives folding when available.

The visible `ycm_global_extra_conf.py` is a legacy-capable C/C++ configuration
file. The current `init.lua` does not install or initialize YouCompleteMe, so it
must not be described as part of the current active plugin list.

## 2020 editor evidence

In his 2020 Codeforces AMA, Andrew called Vim his favorite editor and JetBrains
IDEs the runner-up. He described YouCompleteMe as the most important plugin for
competitive programming, linked his dotfiles and Makefile, and said that at
ICPC World Finals he typed the short Vim config from `icpc-book`.

He also posted a Google Kick Start Round E screencast with a quick setup and
template showcase: https://www.youtube.com/watch?v=ExmrrXi04vI. It is not a
dedicated setup video, and no transcript is saved.

## Plugin-free ICPC Vim configuration

`sources/github/repos/icpc-book/content/contest/vimrc` is seven lines long. It
enables standard indentation, highlighting, search, line numbers, mouse,
syntax, and filetype indentation; maps `gA` to copy the entire file to the
system clipboard; and defines preprocessing/hash commands used to produce a
whitespace-insensitive MD5 for notebook code. It has no plugin dependency.

The related `kactl_bashrc` defines a warning-heavy C++14 compile alias with
UndefinedBehaviorSanitizer and AddressSanitizer, and remaps Caps Lock to `<` and
`>` through `xmodmap`.

## Current contest workflow (2026 snapshot)

The maintained workflow is in `cp-book/contest/`:

- `make_prob.py` creates problem directories from layered `.template`
  directories, allowing global, site-specific, and contest-specific overrides.
- `download_prob.py` listens on localhost for Competitive Companion data and
  saves problem metadata and samples.
- `__PROBLEM_NAME__` is substituted in file names and contents.
- The generated `setup` script flattens optional Makefile hooks and runs
  `bear -- make all` to produce `compile_commands.json` for clangd.
- The default source template is intentionally tiny: headers, assertions, fast
  iostream setup, and `main()`.

The Makefile defaults to GNU C++23 with `-O2`, debug symbols, extensive
warnings, ASan, UBSan, libstdc++ debug modes, and stack protection. It caches
precompiled standard headers by a hash of the compiler and flags, archives a
timestamped source copy before each build, times runs, runs all `*.in` cases,
and diffs generated `*.res` files against `*.out` files. Debug checks can be
disabled through `DEBUG := false`.

The `cp-book` library is separate from contest programs. Required headers can
be copied or bundled into a standalone submission with `scripts/bundle.py`,
including a minification mode for Codeforces size limits.

## Historical template systems

### `cptemp` (2015)

The oldest saved template is a bare C++11 `main()` using `<bits/stdc++.h>`. Its
Makefile provides strong warnings, optional debug/sanitizer flags, automatic
target naming from the directory, timed execution, sample result generation,
and `diff` checks. `make_prob.sh` creates one directory per requested problem
and copies the template and Makefile.

### Makefile and template-system gists

The maintained Makefile gist is a C++17 predecessor of the present `cp-book`
Makefile. It includes sanitizer/debug modes, precompiled headers, timed runs,
and sample diffs. The template-system gist uses upward-searching layered
`.template` directories and a Competitive Companion listener. Its current
repository successor is `cp-book/contest/`.

## Shell and terminal evidence

The dotfiles contain Bash, Zsh, tmux, iTerm, mintty, X11, and other historical
configuration. The current Zsh file uses Oh My Zsh with the `bureau` theme,
sets Neovim as editor, configures Solarized fzf colors for several terminals,
and provides navigation/history behavior. An iTerm Solarized color file is
present. These files show cross-machine history; there is no single dated
hardware or terminal walkthrough establishing which terminal is currently
primary.

## What remains unknown

- No standalone setup video or setup transcript was found.
- Current hardware, operating system, terminal emulator, and exact live plugin
  state are not directly documented.
- The public dotfiles span old and new configurations, so presence alone does
  not prove current use.
