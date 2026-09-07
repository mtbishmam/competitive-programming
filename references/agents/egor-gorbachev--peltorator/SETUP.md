# Competitive-programming setup — peltorator

## Evidence date and scope

This setup is documented by Egor's dedicated video published on 2021-06-28,
its supplied transcript, its full live description, and the exact linked
Pastebin files. It is strong evidence for his setup at that time, but not proof
of his current 2026 machine or configuration.

## Hardware and supporting tools

- Late-2020 13-inch MacBook Air with Apple M1.
- The transcript reports a 512 GB SSD. Its automatic transcription renders the
  RAM amount as “60 gigs,” which is not a credible hardware value, so the exact
  memory capacity is left unresolved rather than guessed.
- Blue Yeti microphone for videos.
- One by Wacom tablet for drawing during explanations.
- Autodesk SketchBook for drawing.
- A temporary Dell UltraSharp 38-inch curved monitor during his internship;
  he said he normally did not use an external monitor.

## Codeforces browser extensions

He demonstrated CF Predictor for estimated live rating changes and Codeforces
Enhancer. In the latter, he discussed hiding solved problems, language-colored
standings, incorrect-attempt counts, and multiple rating graphs. At publication
time he disabled language coloring for hacking and said the multiple-graph
feature no longer worked after a Codeforces change; his remaining practical use
was the incorrect-attempt count.

These Chrome Web Store links and extension behavior are historical. Current
availability or compatibility is not established by the archive.

## Vim and MacVim

Egor said he used Vim for essentially all code and text files and preferred
MacVim because it provided a friendly standalone application. He explicitly
recommended choosing an editor by personal fit rather than copying Vim merely
because he used it.

Exact file: `artifacts/dotfiles/vim/.vimrc`.

Editor behavior:

- Jellybeans color scheme and Menlo Regular 16-point GUI font.
- Four-space indentation expanded to spaces, C indentation, syntax and
  filetype indentation, absolute line numbers, search highlighting,
  incremental/case-insensitive search, disabled swap files and bells.
- `F1` goes to the previous tab; insert-mode `F1` exits insert mode.
- `F3` writes and invokes the filetype-specific `makeprg`.
- `F7` pipes the current buffer through Python 3.
- `Tab` is mapped to Vim's `%` matching-item movement in normal mode.
- Space is the leader. Leader mappings include buffer start, file explorer,
  redo, split navigation, vertical split, quit, jump-list movement, select all,
  comment insertion, and re-sourcing `.vimrc`.
- Filetype `makeprg` commands cover C++, Haskell, Python, and shell files.

### Compile-and-run keys

All three active C++ mappings save, compile with GNU C++17, ASan, `-DONPC`, and
`-O2`, then run the output:

- `F8`: omits the warning flags and reads stdin from `inp`; intended for code
  copied during a contest when warnings are noisy.
- `F9`: enables `-Wall -Wextra -Wshadow` and runs interactively without `inp`;
  useful for interactive programs.
- `F10`: enables those warnings and reads stdin from `inp`; this is the normal
  local problem workflow shown in the video.

The normal- and insert-mode versions differ slightly in filename quoting. These
commands are historical and assume GNU `g++`, a local `inp` file, and a
toolchain where AddressSanitizer works.

## Vim plugins and snippets

Vim-Plug manages:

- VimTeX for LaTeX.
- UltiSnips for snippet expansion.
- `vim-snippets` as an additional snippet collection.

UltiSnips expansion and forward-jump both use `Tab`; backward jump uses
`Shift-Tab`. The exact linked C++ file is
`artifacts/snippets/cpp.snippets` and contains 32 triggers.

The video demonstrates `beg` + `Tab` for the full template, `minimal` for a
small template, parameterized loop expansion, and `{` + `Tab` for a brace
block. Egor explicitly warned that some snippets were outdated even in 2021
and should be reviewed rather than copied blindly.

## The `beg` C++ template

The full UltiSnips template uses:

- `#ifdef ONPC` before the standard header to enable `_GLIBCXX_DEBUG` only in
  local builds.
- `<bits/stdc++.h>`, `using namespace std`, `ll`, and `ld` aliases.
- `sz(a)` to cast container size to signed `int`.
- `#define char unsigned char`, motivated in the video by safe byte-array
  indexing; this is invasive and should not be treated as general C++ advice.
- A time-seeded `mt19937`, with a commented constant-seed alternative for
  non-hackable team contests.
- `solve()` returning nonzero when input is exhausted.
- A default large test-loop bound so EOF can terminate multi-case local input;
  a conventional `cin >> TET` line can be uncommented when `T` is explicit.
- `ONPC`-only separators between local cases and total runtime reporting.
- Fast iostream setup. The transcript records Egor removing a useless
  `cout.tie(0)` while preparing the video; the saved linked snippet contains
  only `cin.tie(0)`.

The `minimal` trigger produces only the standard header, namespace, `ll`, and
an empty `int32_t main()`.

## Algorithm snippets

Beyond small typing helpers, the file embeds implementations for GCD, binary
exponentiation, modular inverse, FFT, suffix array, Aho–Corasick, convex hull
trick, segment tree, centroid decomposition, sparse table, treap, Fenwick and
2D Fenwick trees, modular arithmetic, DSU, and local debug printing. The exact
trigger map and caveats are in `CODE_INDEX.md`.

In the video Egor described the FFT as based on tourist's version and the
segment tree as also coming from tourist. Those snippets must not be attributed
to Egor as original implementations without more specific provenance.

## Terminal

He used iTerm2 with Oh My Zsh. The video gives no complete `.zshrc`, iTerm2
profile export, shell theme, or terminal color configuration, so those details
are not recoverable from the current evidence.

## What remains unknown

- No current post-2021 editor/setup update or current dotfiles repository was
  identified.
- The exact 2021 MacBook RAM capacity is unclear in the transcript.
- No standalone shell configuration, stress-test script used on his machine,
  or general contest-solution archive was found.
- The snippet file itself says some entries were already outdated in 2021.
