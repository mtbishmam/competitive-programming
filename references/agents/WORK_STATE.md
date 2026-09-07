# Archive work state

Paused at the user's request and resumed on 2026-09-07. The requested archive
and documentation pass is now complete. No source-download command or
background process is running. Do not restart discovery or redownload complete
snapshots unless the user asks for a refresh.

## Intended outcome

Maintain a scalable evidence archive for:

- Andrew He / `ecnerwala`
- Jay Leeds / `Geothermal`
- Egor Gorbachev / `peltorator`

For relevant future questions, answer in this order: general answer,
ecnerwala's documented version, Geothermal's documented version, and
peltorator's documented version. State missing evidence instead of inferring.

## Completed

- Migrated the earlier `references/users/` tree to `references/agents/`.
- Added persistent answer rules to the repository-root `AGENTS.md`.
- Added archive rules in `references/agents/AGENTS.md`.
- Created `references/agents/INDEX.md` with coverage and known gaps.
- Saved official Codeforces API profile snapshots for all three people.
- Saved complete GitHub profile/repository-list JSON for ecnerwala and
  peltorator.
- Searched GitHub for Jay Leeds and saved the result. `jsleeds` remains an
  unverified candidate and is not attributed to Geothermal.
- Saved both supplied transcripts byte-for-byte:
  - Geothermal: 1,516 lines, 34,476 bytes,
    SHA-256 `4edb8b003672085f7feee1f76b4996ffed6b1cc7b099678b065d5c9c6297160d`.
  - peltorator: 1,232 lines, 25,563 bytes,
    SHA-256 `38c38ab1ef7a08fd66bc4f4a090f76df633507c2f89dfec9d6f0b089bcecd522`.
- Saved YouTube oEmbed metadata for both setup videos.
- Downloaded Geothermal's exact linked Pastebin `.vimrc`, template,
  `build.sh`, `stress.sh`, `validate.sh`, `interact.sh`, and `runner.py`.
- Downloaded peltorator's exact linked Pastebin `.vimrc` and 32-trigger C++
  UltiSnips file.
- Finished Geothermal's `README.md`, `PROFILE.md`, `SETUP.md`, `CODE_INDEX.md`,
  `SOURCES.md`, and complete video description.
- Finished ecnerwala's `README.md`, `PROFILE.md`, `SETUP.md`, `CODE_INDEX.md`,
  `SOURCES.md`, Codeforces setup-evidence note, and setup-showcase metadata.
- Finished peltorator's `README.md`, `PROFILE.md`, `SETUP.md`, `CODE_INDEX.md`,
  `SOURCES.md`, and complete live video description.
- Corrected the classification of Andrew's `cvimrc` gist: it is browser
  navigation configuration, not his ICPC Vim configuration.
- Located Andrew's 2020 Kick Start Round E screencast and recorded it as a
  quick setup/template showcase rather than a standalone setup video.
- Verified every linked Pastebin artifact against its live raw SHA-256,
  rechecked both supplied transcripts byte-for-byte, validated source JSON,
  checked authored internal Markdown links, and checked authored files for
  trailing whitespace.

## GitHub snapshots already complete

All are source archives without nested `.git` histories. Do not execute them.

### ecnerwala

| Repository | Branch | Snapshot commit |
|---|---|---|
| `cp-book` | `master` | `6d94fa04f139e11e71352fecbdc8de241fa038c3` |
| `dotfiles` | `master` | `e82049fab91399c04b7f4264b18e3e109d3743b4` |
| `contest-programming` | `master` | `50f2b86bcb59bc417f0c9a2f3f195eb45ad54eb4` |
| `cptemp` | `master` | `a7472e5c98093f50f9133dbcfa6e39e3bcd77b2e` |
| `icpc-book` | `master` | `f21d747074ee8fe2925adccd6e78ea7fbabb70b4` |
| `SPOJ` | `master` | `d0d1e79343bda87b85d2f69fe477e80d80d3dc4c` |
| `TopCoder` | `master` | `c928863360f6bc26fff73634a6ce0a81bf918be4` |
| `traingate` | `master` | `cf7a4ce81d786832b711a6a99d4cc91561901d9e` |
| `competitive-verifier` | `cp-book-integration` | `2efc17bf640e29bbc3a9a22e48ee09a0ab3a4e4e` |
| `cms` | `master` | `1fb11c21c91ce9c09ac8df92555de2927475104b` |
| `kactl` | `master` | `b6231f39445155fc3eeaa1dee150ba1f86464738` |
| `testlib` | `master` | `1713568b1ea0da8993815990a153fa8f7c169ea2` |
| `Num` | `master` | `599814c70c7650258a9e9cdd6b3144be8cca933a` |
| `aoc-2019` | `main` | `9a8a273804395da1d269bea94f260e320946f26c` |
| `CowCatcher` | `master` | `f178d142a8e19729f83461f810249ea76b4be2a6` |
| `synacor-challenge` | `master` | `24c5f8f7a6d279edc9c82fe31052d178490beda5` |

Also saved the current CP template-system gist, Competitive Programming
Makefile gist, and historical `cvimrc` gist. Total ecnerwala repository
snapshot size is approximately 425 MB; `contest-programming` alone contains
7,019 files.

### peltorator

| Repository | Branch | Snapshot commit |
|---|---|---|
| `algorithmica` | `master` | `2bc29382807885b4e03fc215da2917a647f3b6d9` |
| `cp-algorithms` | `master` | `ca07bb0b5e7872289ec7750efa004a2bd9203625` |
| `klees-measure-lower-bounds-repo` | `main` | `56e9495a401f15cf63bc832f683a291ab45947d5` |
| `peltorator-cp-book` | `main` | `db95b2288ab3d8e36c6a6c858959a01928418198` |
| `peltorator.github.io` | `master` | `5548617e9261ab14d4efdf7ac027ba7b6830468a` |
| `segment-tree-beats` | `main` | `7f2550abd7adf33e0f99b8d045879c52cc4ba50a` |

Also saved his public Tinkoff Haskell-circle instruction gist as adjacent
educational context. Total peltorator repository snapshot size is approximately
49 MB.

`BOA-Project` is algorithm research rather than a CP setup/library repository.
Its transfer timed out and left an incomplete 184 MB extraction; that partial
directory was moved recoverably to
`/Users/mtbishmam/.Trash/incomplete-Peltorator-BOA-Project-20260907`. The full
repository remains listed in peltorator's saved `repositories.json` but is not
part of the archive.

## Deliberately not vendored

- Repositories clearly unrelated to CP remain recorded in each account's full
  `repositories.json` inventory.
- Third-party Git submodules were not downloaded. Andrew's dotfiles declare
  Vundle, Oh My Zsh, Solarized dircolors, and Mutt Solarized. Egor's CP book
  declares the Hugo Texify theme.
- Video binaries were not downloaded; URLs, metadata, full descriptions, and
  searchable transcripts are the intended evidence.

## Future refresh work

- Recheck Jay Leeds's GitHub identity if the user provides a link or new public
  evidence appears.
- Refresh point-in-time profile/repository snapshots only when the user asks;
  current snapshots are dated 2026-09-07.
- Add future people through the same five-document structure and update
  `INDEX.md`.
- Do not repair broken links inside vendored upstream repository snapshots;
  those trees are preserved evidence.

## Worktree protection

The following non-reference changes existed during this work and were not
modified as part of the archive task:

- Modified: `practice/2171C1.cpp`
- Deleted: `practice/cf/2202A.cpp`
- Untracked: `contests/ssc/ssc-analysis.md`
- Untracked practice files including `1475E.cpp`, `1528A.cpp`, `2202A.cpp`,
  `2218A.cpp`, `2218B.cpp`, and `2218C.cpp`

Future archive work should stay inside `references/` and the already-authorized
reference section of the root `AGENTS.md` unless the user broadens scope.
