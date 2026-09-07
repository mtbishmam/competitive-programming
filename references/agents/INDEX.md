# Competitive-programmer reference index

Captured and audited on 2026-09-07. The archive currently tracks three people:

- [Andrew He — ecnerwala](andrew-he--ecnerwala/README.md)
- [Jay Leeds — Geothermal](jay-leeds--geothermal/README.md)
- [Egor Gorbachev — peltorator](egor-gorbachev--peltorator/README.md)

## Coverage matrix

| Evidence | ecnerwala | Geothermal | peltorator |
|---|---|---|---|
| Codeforces profile | Verified; API snapshot saved | Verified; API snapshot saved | Verified; API snapshot saved |
| GitHub identity | Verified: `github.com/ecnerwala` | Unresolved; no account safely linked | Verified: `github.com/Peltorator` |
| Complete public GitHub inventory | Saved as JSON | Candidate search saved only | Saved as JSON |
| CP-related GitHub snapshots | 16 repositories, 2 CP/tooling gists, and 1 adjacent dotfile gist | None found | 6 selected repositories plus 1 adjacent gist |
| Dedicated setup video | No standalone video; 2020 screencast has a setup showcase | Verified and transcribed | Verified and transcribed |
| YouTube channel | Verified: `@ecnerwala` | Verified: `@geothermaljl` | Verified: `@peltorator` |
| Video description | Setup-showcase announcement and oEmbed saved | Full description saved | Full description saved |
| Editor/dotfiles | Full current dotfiles; historical ICPC Vim config | Pastebin `.vimrc` | Pastebin `.vimrc` |
| C++ template | Current, ICPC, and historical templates | Pastebin `Template.cpp` | `beg` and `minimal` UltiSnips templates |
| Build/test tooling | Current contest system, Makefiles, downloader | Build, stress, validator, interaction scripts | Vim compile mappings, snippets, stress article |
| Custom algorithm/data-structure library | Current `cp-book`; historical `icpc-book` | No library located | CP book, 32 snippets, segment-tree-beats work |
| Historical solution archive | Multiple repositories, including 7,019-file archive | No repository located | No general solution archive located |

## Default answer order

For setup, template, tooling, algorithm, and data-structure questions:

1. General answer.
2. ecnerwala's documented approach.
3. Geothermal's documented approach.
4. peltorator's documented approach.

If the question concerns something not documented for one person, retain that
section and state the gap briefly. If the user asks about one person only or
requests a different format, follow that request.

## Known gaps

- Jay Leeds's GitHub account is unresolved. GitHub search returned a `jsleeds`
  account named Jay Leeds, but it has no public repositories and no public link
  to `Geothermal`; it is not treated as his account. Direct checks for
  `jayleeds`, `geothermaljl`, and `GeothermalJL` returned no GitHub user.
- No standalone ecnerwala setup video or transcript was found. His 2020 Google
  Kick Start Round E screencast includes a quick setup/template showcase
  according to his own Codeforces announcement; the announcement, video URL,
  oEmbed metadata, current dotfiles, contest tooling, AMA answer, and YouTube
  channel are documented.
- No separately linked peltorator C++ template was found. His `beg` and
  `minimal` templates are embedded in the supplied UltiSnips file and are
  indexed locally.
- No general peltorator contest-solution repository was identified among his
  public repositories.
- Third-party Git submodules are recorded but not vendored. Andrew's dotfiles
  declare Vundle, Oh My Zsh, Solarized dircolors, and Mutt Solarized. Egor's
  selected snapshots also contain unpopulated theme/plugin submodule paths.
- Video binaries were not downloaded. The canonical URLs, complete
  descriptions, metadata, and verbatim transcripts are saved, which is the
  useful searchable evidence for future answers.
- GitHub and Codeforces data are point-in-time snapshots and may drift.

## Repository-selection boundary

Original CP repositories, historical contest code, dotfiles, contest tooling,
and clearly relevant forks were snapshotted. Public repositories unrelated to
CP remain represented in each complete `repositories.json` inventory but were
not copied. Egor's `BOA-Project` was classified as algorithm research rather
than CP; an incomplete timed-out download was moved to the macOS Trash and is
not part of this archive.
