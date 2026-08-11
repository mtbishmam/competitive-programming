# SSC Replay Workflow

These instructions apply to every SSC replay run under
`/Users/mtbishmam/code/competitive-programming/contests/ssc`.

The current authoritative VJudge instructions are
`https://vjudge.net/article/17624`. Treat that article as the source of truth
if VJudge changes its Replay workflow. Article 87 is historical guidance only.

The trigger is the explicit token `replay_ssc`. Do not start this workflow for
an ordinary SSC question, a normal solution, or a request that does not contain
`replay_ssc`.

## Goal

Turn a private SSC VJudge contest's final rank export into a VJudge Replay
workbook that can be uploaded after the problem set has been entered in the
same order.

Article 17624 recommends URL import only for supported remote contest URLs.
The currently supported list is Codeforces regular contests, Codeforces Gym,
and QOJ. An SSC contest hosted inside VJudge is not one of those remote-import
sources, so use the manual Rank Excel workflow unless VJudge later adds direct
support for the actual upstream source contest.

The workflow accepts both inputs in one user message:

1. an ordered problem mapping pasted by the user; and
2. the rank workbook downloaded from VJudge and placed in the global `ssc`
   folder.

VJudge needs both. The rank workbook normally labels columns only as `A`, `B`,
`C`, etc.; it does not reliably carry the OJ and problem identifiers needed to
recreate the Problem Set. Therefore the mapping file is not redundant.

The two Excel files have different jobs and must never be swapped:

| File | Use |
|---|---|
| `ssc-round-<round>-ranklist.xlsx` | Local source/archive only; do **not** upload this to VJudge Replay Info. It contains `Rank`, `Team`, `Score`, `Penalty`, `A`, `B`, ... |
| `ssc-round-<round>-vjudge-replay.xlsx` | Upload this in VJudge **Replay Info -> Upload rank Excel**. It has no header row: participant name first, then one replay-status cell per problem. |

If VJudge shows a generic `[object Object]` error after upload, first verify
that the selected file is the `-vjudge-replay.xlsx` file, not the moved
`-ranklist.xlsx` source. The raw ranklist is retained as the local source and
audit archive; it is not the Replay upload format.

Use the article 17624 `minute:second` / parenthetical-count convention. When
VJudge asks what the sample cells mean, use these exact interpretations:

- blank → `No submission`;
- `(-N)` → `Not solved, with N wrong submission(s)`;
- `M:SS` → `Solved at M min SS sec with no wrong submission`; and
- `M:SS(-N)` → `Solved at M min SS sec with N wrong submission(s)` before the
  accepted submission.

`M` is total elapsed minutes and may exceed 59. For example, `119:35` means
accepted at 119 minutes 35 seconds with no wrong submission, and
`177:57(-4)` means accepted at 177 minutes 57 seconds after four wrong
submissions. This preserves the source's second-level precision while avoiding
an extra numeric component.

Article 17624 does not require one fixed syntax, but the current VJudge UI can
render the mapping selector blank for four-number patterns such as
`5 # 2:57:57` or `2:57:57(-4)`. Do not generate those patterns for SSC. Do not
use slash forms such as `H:MM:SS/T`, either. Do not confirm until every detected
format has a visible interpretation selected.

## Contest registry

Use `ssc-contest-links-aug-11.md` as the local source of truth for SSC title,
VJudge URL, contest ID, and password. Resolve a user-provided SSC name or URL
against that file before doing anything else.

- Match titles case-insensitively after trimming Markdown formatting.
- Match a VJudge URL by its numeric contest ID.
- Do not guess a password, contest ID, season, round, or replacement contest.
- Do not copy passwords into generated files, problem manifests, commit
  messages, or ordinary replies. Use the registry only when the user needs to
  access the private contest.
- If the registry has no unambiguous match, stop and ask for the exact title or
  URL.

The registry currently covers Summer 2025, Fall 2025, Spring 2026, and Summer
2026 entries. The Markdown registry may be extended later without changing
this workflow.

## Required folder layout

Every generated replay must live in a new, contest-specific folder. The global
`ssc` root is an intake folder only: the user may place the newly downloaded
ranklist there, but generated artifacts must be moved or written into the new
run folder. Never overwrite a previous run.

Derive the path from the normalized registry title:

```text
<season>-<year>/ssc-round-<round>/
```

For example:

```text
fall-2025/
└── ssc-round-1/
    ├── ssc-round-1-ranklist.xlsx
    ├── ssc-round-1-problems.md
    └── ssc-round-1-vjudge-replay.xlsx
```

Canonicalize the ranklist basename to
`ssc-round-<round>-ranklist.<original-extension>`. Preserve the original
extension: an Excel workbook remains `.xlsx` (or `.xls`), and a text ranklist
may remain `.md`, `.csv`, or `.tsv`. Never rename binary Excel data to `.md`;
that would make the ranklist unreadable and prevent workbook parsing.

Use lowercase `summer`, `fall`, or `spring` and the four-digit year. Use the
round number from the title, not the VJudge contest ID.

If the deterministic folder already exists, create a fresh sibling run folder
such as `ssc-round-1-run-20260811-1430`; do not overwrite or silently mix
files from the existing run. The source rank workbook's contents must remain
unchanged; moving it and canonicalizing its basename are allowed only after
validation.

## `replay_ssc` procedure

The intended request is one message containing the trigger, the SSC title or
URL, and the complete problem block:

```text
replay_ssc SSC Round 1 | Summer 2025
[problem:AtCoder-abc462_c] A - A
[problem:CodeForces-2246C] B - B
[problem:CodeForces-2224A] C - C
[problem:AtCoder-abc407_a] D - D
```

Do not ask the user to repeat the password or contest ID when the registry has
an exact match.

### 1. Resolve the contest and find the ranklist

1. Resolve the title or URL, VJudge ID, season, year, and round from the
   registry.
2. Parse the complete `[problem:...]` block from the same message.
3. Search only the global intake directory
   `/Users/mtbishmam/code/competitive-programming/contests/ssc` for one
   unprocessed ranklist file. Candidate extensions are `.xlsx`, `.xls`,
   `.csv`, `.tsv`, and `.md`.
4. Exclude `AGENTS.md`, the contest registry, existing Replay outputs, and
   files already inside a generated season/round folder. Identify the ranklist
   by its content/header, not by a guessed filename.
5. If there is no candidate, or if more than one candidate remains, stop and
   tell the user exactly which files need to be left in the global intake
   directory.
6. Validate the problem block and ranklist structure before moving anything.

After validation, create the new season/round folder. If its deterministic
folder already exists, create a fresh `-run-YYYYMMDD-HHmm` sibling. Move the
ranklist into that folder and rename only its basename:

```text
Rank-SSC Round 1 _ Summer 2025.xlsx
→ summer-2025/ssc-round-1/ssc-round-1-ranklist.xlsx
```

Never overwrite an existing destination. If the source is a text ranklist, use
the same canonical basename with its original `.md`, `.csv`, or `.tsv`
extension. Do not rename an Excel workbook to `.md`.

### 2. Accept and validate the problem mapping

The user may paste workbook/problem information like this:

```text
[problem:AtCoder-abc462_c] A - A
[problem:CodeForces-2246C] B - B
[problem:CodeForces-2224A] C - C
[problem:AtCoder-abc407_a] D - D
[problem:CodeForces-2246D] E - E
[problem:CodeForces-2224C] F - F
[problem:CodeForces-2167F] G - G
[problem:AtCoder-abc405_a] H - H
```

The generated `ssc-round-<round>-problems.md` must contain one plain,
pipe-delimited line per problem, in contest order:

```text
AtCoder | abc462_c | 1 |
CodeForces | 2246C | 1 |
CodeForces | 2224A | 1 |
AtCoder | abc407_a | 1 |
CodeForces | 2246D | 1 |
CodeForces | 2224C | 1 |
CodeForces | 2167F | 1 |
AtCoder | abc405_a | 1 |
Gym | 320558L | 1 |
```

The fourth field is reserved for an optional VJudge alias and is empty unless
the user explicitly supplies one. Preserve the problem order and weight; do
not sort by platform, difficulty, title, or problem key.

The accepted labels are case-insensitive input aliases for `AtCoder`,
`CodeChef`, `CodeForces`, `Gym`, and `CSES`; write the canonical labels shown
above.
The problem identifier is the exact VJudge/contest identifier supplied by the
user. Do not replace it with a filename, title, frontend number, or a guessed
slug.

Before writing the file, validate:

- every problem has exactly one alias (`A`, `B`, ..., in order);
- aliases are unique and contiguous;
- every line has an OJ, problem key, weight, and optional alias field;
- weights are numeric and normally `1`;
- the supported OJ is known; and
- no problem was silently dropped, duplicated, or reordered.

If the rank workbook later has a different number of problem columns than this
mapping, stop and report the mismatch instead of generating a misleading
Replay file.

### 3. Write the problems file and validate the moved ranklist

Write `ssc-round-<round>-problems.md` in the new folder immediately after the
mapping passes validation. Then validate the moved ranklist:

For a normal VJudge rank export, expect a header similar to:

```text
Rank | Team | Score | Penalty | A | B | C | ...
```

Validate the workbook before conversion:

- identify the actual rank sheet and its used range;
- confirm that the participant and problem columns are present;
- confirm that problem columns match the mapping aliases in count and order;
- preserve the participant/team text exactly;
- verify solved counts against the source `Score` when available; and
- verify the source penalty totals before exporting.

If the workbook is a screenshot, PDF, partial page, or a different table
layout, do not guess at cells. Ask for the original Excel export or a complete
rank table.

### 4. Generate the VJudge Replay workbook

Create a new workbook in the same run folder. The Replay workbook is a parser
input, not a report, so it must contain:

- no header row;
- the participant/team name in column 1;
- one column per problem, in the exact mapping order; and
- no copied `Rank`, `Score`, or `Penalty` columns.

Enforce the current article 17624 upload constraints:

- output `.xls` or `.xlsx`; use `.xlsx` for generated SSC files;
- keep the file at or below the current 10 MB upload limit;
- put replay data on the first sheet (prefer exactly one sheet);
- include at least 1 and at most 5000 teams;
- do not exceed the number of problems already added to the Replay form; and
- keep the generated replay at or below 50000 submission events.

Use this article-17624-compatible status encoding:

```text
12:22       solved at 12 minutes 22 seconds with no wrong submission
19:46(-1)   solved at 19 minutes 46 seconds after one wrong submission
137:36      solved at 137 minutes 36 seconds with no wrong submission
(-8)        not solved, eight failed submissions recorded
             no submission
```

The accepted time must be preserved to the precision present in the source
ranklist. Convert `H:MM:SS` to total `M:SS` without rounding or dropping the
seconds. For a solved source cell with `(-n)` below the time, append the same
`(-n)` to `M:SS`. For an unsolved source cell, preserve `(-n)`.

Do not claim that the Replay reconstructs the exact original timestamps of
failed submissions: a final rank export generally provides counts, not the
individual failed-submission times. Accepted times and attempt counts are the
recoverable data.

The generated workbook should use a clear name such as:

```text
ssc-round-<round>-vjudge-replay.xlsx
```

It must be written only inside the new run folder beside the moved source
ranklist and problems file. Do not modify the ranklist contents, the registry,
or unrelated contest folders.

### 5. Manual VJudge fallback

Codex prepares the local artifacts and may complete the Replay creation in the
logged-in VJudge browser when the user explicitly invokes `replay_ssc` with a
specific SSC contest. Do not claim that a Replay was created, uploaded,
cloned, or started unless that action was actually completed and independently
verified.

If browser-assisted creation is not being used, the user can:

1. open the resolved private VJudge contest;
2. choose Create Contest → Replay;
3. enter the same problems from `ssc-round-<round>-problems.md` in the same
   order;
4. set the contest length and scoring/penalty settings to match the source
   contest;
5. open Replay Info and upload the generated Replay workbook;
6. assign the correct meaning to every detected cell pattern;
7. make the Replay public, because article 17624 requires contributed replays
   to be public;
8. confirm/create the Replay and independently verify its VJudge page and ID.
9. The user clones the Replay manually for the personal virtual run. Do not
   clone or schedule it unless the user explicitly asks for that separate
   action.

For scheduled virtual runs, interpret times in `Asia/Dhaka` unless the user
explicitly supplies another timezone. Convert that local time to the format
shown by VJudge before saving the cloned contest.

The source contest must already have ended. Use its real original begin time
and duration. Add the original contest URL and standings source to the
description when possible, but never include the contest password.

For step 5, upload only `ssc-round-<round>-vjudge-replay.xlsx`. Do not upload
`ssc-round-<round>-ranklist.xlsx`; that file is retained as the local source
and audit archive.

The exact length and penalty must come from the source contest/rank data. Do
not assume that every future SSC contest uses four hours or a 1200-second
penalty. If the rank data cannot establish one consistent penalty, stop and
ask the user to confirm the VJudge scoring settings.

### Optional browser-assisted creation

For an explicit `replay_ssc` request, Codex may use the user's
already-authenticated VJudge browser session to fill and confirm the Replay
form from the generated files:

1. open the resolved VJudge contest;
2. open Create Contest and choose Replay;
3. fill the original title, begin time, duration, public openness, and ICPC
   ranking settings;
4. enter the problems from `ssc-round-<round>-problems.md` in order;
5. upload `ssc-round-<round>-vjudge-replay.xlsx`;
6. choose and verify every cell-format interpretation, including ICPC wrong
   submission counts; and
7. click the final Create Contest confirmation, then independently verify the
   resulting Replay page and ID.

Do not inspect or extract cookies, passwords, local storage, or session data.
Do not paste the registry password into chat or generated files. Cloning the
Replay into a practice contest is a separate action and remains the user's
manual step unless explicitly requested.

### API assessment

As of this workflow version, VJudge has no documented, supported public API for
creating a manual Replay from a problem set and rank Excel file. The current
official guide documents only remote-URL import for supported sources and the
manual Replay form with Excel upload:
`https://vjudge.net/article/17624`.

Community packages described as “Vjudge API” are unofficial and expose selected
read/status helpers; they are not a stable Replay-creation contract. Do not
reverse-engineer or depend on VJudge's private browser endpoints, CSRF tokens,
or session cookies. Use the browser-assisted procedure above when the user
explicitly requests creation.

## Simpler approach assessment

The one-message workflow is the simplest safe approach available locally:

```text
replay_ssc + SSC title/URL + ordered problem block
→ find exactly one ranklist in the global ssc intake folder
→ validate both inputs
→ create a fresh season/round folder
→ move and canonicalize the ranklist
→ write the problems file and Replay workbook
```

VJudge still requires two kinds of data: the Problem Set identifiers/order and
the Replay rank workbook. Combining them into one future `contest.json` or TSV
would reduce internal file count, but it would not remove either required data
source or the final VJudge upload step. Do not add that extra format until it
provides a concrete benefit.

## Test run

To test the workflow, leave exactly one fresh rank export directly in the
global `ssc` folder, then send one message in this shape:

```text
replay_ssc SSC Round 1 | Summer 2025
[problem:AtCoder-abc462_c] A - A
[problem:CodeForces-2246C] B - B
[problem:CodeForces-2224A] C - C
[problem:AtCoder-abc407_a] D - D
```

Use the real complete problem block for the selected contest; the four-line
block above is only a syntax example. The test should produce a new folder
like:

```text
summer-2025/ssc-round-1/
├── ssc-round-1-ranklist.xlsx
├── ssc-round-1-problems.md
└── ssc-round-1-vjudge-replay.xlsx
```

The test passes only if:

- the title or URL resolves to one registry entry;
- the ranklist is moved out of the global intake folder without changing its
  contents;
- the source extension is preserved;
- the problems file has the same number/order of aliases as the ranklist;
- the Replay workbook has no header and excludes Rank/Score/Penalty columns;
- solved counts and source penalty totals reconcile; and
- the workbook satisfies the current article 17624 file-size, team-count,
  problem-count, and event-count limits; and
- no existing folder or file was overwritten.

After inspecting those three files, upload the generated Replay workbook in
VJudge's Replay Info tab, confirm the Problem Set order from the problems file,
create the Replay, and clone it for the actual virtual attempt.

## Adding support for another OJ

When a new judge is added, update this file before using it in a generated
mapping. Add:

1. the accepted input labels and one canonical output label;
2. the exact VJudge problem-key format and a valid example;
3. URL/key parsing rules, if URLs will be accepted;
4. case-normalization rules;
5. how the key maps to a ranklist column; and
6. a validation example and a failure case.

Current adapter notes:

| OJ | Canonical label | Key rule | Example |
|---|---|---|---|
| AtCoder | `AtCoder` | Preserve the supplied VJudge key, such as a live-contest key or contest-task slug. | `atcoder11live_a` or `abc462_c` |
| CodeChef | `CodeChef` | Use the supplied problem code; normalize to uppercase when the key is a CodeChef code. | `NEWBIE07` |
| CodeForces | `CodeForces` | Use contest ID plus canonical uppercase index. | `384A` or `2246C` |
| Gym | `Gym` | Use the VJudge Gym problem identifier, preserving the contest ID and problem index. | `320558L` |
| CSES | `CSES` | Use the stable numeric task key. | `2129` |

Unknown OJs must be reported as unsupported. Never silently map them to a
similar platform.

## Safety and mutation boundaries

- Read existing files before writing anything.
- Do not alter ranklist contents, registry files, or existing run folders. The
  one permitted intake mutation is moving one validated ranklist from the
  global `ssc` root into the newly created run folder and changing only its
  basename while preserving its extension.
- Do not commit passwords, cookies, or other VJudge credentials.
- Do not commit generated Replay workbooks unless the user explicitly asks;
  they are contest artifacts, not source code.
- Keep every generated artifact inside the new run folder and report its full
  path.
- If any identity, problem order, column count, or scoring assumption is
  ambiguous, stop before generating the workbook and ask for the missing
  input.
