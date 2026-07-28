# Repository Guidelines

## Project Role

This repository is the Codex-facing user interface for the personal CP learning
system. The source code remains the user's normal competitive-programming
workspace; when explicitly requested, Codex also interviews the user about a
solved problem and saves the reflection through the `cp-app` MCP server.

Optimize for learning and extremely low friction. A normal capture should
require only a problem URL and natural answers, and should finish in roughly
five minutes. Preserve raw thinking; generated classifications can be rebuilt
later.

Keep responsibilities separated:

- This repository and Codex own the conversation, local solution context, and
  presentation of the final reflection.
- Deterministic platform adapters own URL parsing and metadata extraction.
- The `cp-app` MCP server owns validation, identity, persistence, idempotency,
  and review scheduling.
- Never write directly to a database from this repository, expose database
  credentials, or claim that a reflection was saved without a successful MCP
  response.

## Project Structure & Module Organization

- `practice/` contains flattened judge solutions directly at its root and
  should not contain platform or topic subdirectories.
- Move reusable or topic-study implementations out of `practice/algo/` and
  into the appropriate `templates/` topic before removing the old directory.
- `contests/` stores contest-specific work under organizers such as `codeforces/`, `atcoder/`, and `icpc/`. Many contest folders include local input, expected-output, generator, and stress-testing files.
- `templates/` contains reusable C++ snippets organized by subject, including `data-structures/`, `graph-theory/`, `number-theory/`, and `strings/`.
- `scripts/` provides helpers for creating, compiling, and checking solutions. There is no central application or asset pipeline.

The worktree already contains partial moves and generated artifacts. Never
bulk-move, rename, or delete practice files merely because the target layout is
documented here. First generate a dry-run manifest containing old path, proposed
path, platform, canonical problem key, URL when known, and content hash. Stop on
missing identities or collisions. Move files only after the user approves a
collision-free manifest, and verify counts and hashes afterward.

## Build, Test, and Development Commands

Solutions are independent C++ programs. Compile from the repository root:

```sh
g++ practice/1914C.cpp -std=gnu++20 -g -Wall -Wshadow -o /tmp/1914C
/tmp/1914C < input.txt
```

When `scripts/` is on `PATH`, `cf 1914C` compiles and runs `1914C.cpp` in the current directory. Contest problem folders may provide:

```sh
./run.sh a       # compile a.cpp, run with `in`, and diff against `exp`
./stress.sh      # compare optimized `code` with brute-force `bf`
```

Read a helper before using it; file names and compiler commands vary between older contest directories.

## Coding Style & Naming Conventions

Use C++20-compatible GNU C++. Follow the nearby solution or template rather than reformatting unrelated code. Existing files generally use four-space indentation, braces on the same line for control flow, short competitive-programming identifiers, and `solve()` plus `main()` for multi-test input.

For flattened judge solutions, use:

- Codeforces: contest ID plus index, preserving multi-character indices, such
  as `2179D.cpp` or `2202C1.cpp`.
- AtCoder: full contest slug, underscore, and task letter, such as
  `abc468_b.cpp` or `arc205_a.cpp`.
- CodeChef: `cc_` plus the lowercase problem code, such as `cc_swapsm.cpp`,
  `cc_btar.cpp`, or `cc_magnetsort.cpp`.
- CSES: the official problem title in underscore-separated title case,
  preserving Roman numerals, such as `Coin_Combinations_I.cpp`.
- LeetCode: `lc_` plus the canonical title slug converted from kebab-case to
  lowercase snake_case, such as `lc_two_sum.cpp` or
  `lc_trapping_rain_water.cpp`. Do not add the frontend problem number.

Keep reusable implementations topic-named, such as `dijkstra.cpp`. Do not
commit generated binaries, `.dSYM/`, swap files, `.DS_Store`, or temporary
runner files.

Filenames are convenient locators, not database identities. The MCP payload
must use `(platform, problem_key)`:

- `codeforces / 2179:D`
- `atcoder / abc468_b`
- `codechef / SWAPSM`
- `cses / 1620`
- `leetcode / 1`

Normalize CodeChef keys to uppercase and Codeforces indices to their canonical
uppercase form. Do not use a bare filename as a primary key. If a proposed
flattened filename already exists with different content, stop and report the
collision; do not silently overwrite it or invent a suffix.

## Reflection Workflow

Enter this workflow only when the user explicitly asks to reflect on, review,
record, save, or be interviewed about a solved problem. Do not interrupt
ordinary coding, debugging, or solution coaching with reflection questions. If
the problem is still unsolved, coach with incremental hints and wait until the
user says it is solved before offering persistence.

1. Obtain the canonical problem URL. Locate a likely solution from the naming
   rules, but ask before choosing when multiple files are plausible.
2. Read the user's solution when available. Obtain a copied statement only when
   the platform adapter cannot fetch normalized problem content.
3. Fetch metadata programmatically before spending model tokens on extraction,
   but do not reveal official tags until the user has explained their own
   reasoning.
4. Ask one adaptive question at a time, normally four to seven questions.
   Cover the first approach, assumptions and why they seemed reasonable,
   failure or stuck point, breakthrough observation, and the reusable trigger
   for next time. Follow the user's answers instead of rigidly reading a form.
5. Preserve the complete raw transcript, including the exact user wording.
   Never replace it with only a generated summary.
6. Produce the structured summary, propose tomorrow as the default first review
   date in `Asia/Dhaka`, and let the user choose another date when desired.
7. Invoke one atomic `save_reflection` MCP call. Display the compact summary,
   saved identifiers, and confirmed next-review date returned by the tool.

The structured summary should contain:

- `key_insight`
- `wrong_mental_model`
- `why_believed_it`
- `correct_trigger`
- `missing_concepts`
- `general_pattern`
- `cognitive_mistakes`
- `next_time_cue`
- `confidence` from 1 through 5

When available, send the MCP server the canonical URL, normalized metadata,
source path, optional source snapshot, immutable transcript, structured
summary, and requested first-review date. The save must be idempotent and
atomic. On a timeout, query for the existing reflection before retrying.

If the MCP server is unavailable, finish the interview and return a valid,
copyable payload, clearly marked **not saved**. Do not improvise a second
database, commit a live database file, or report a successful save.

## Metadata Extraction

Use deterministic adapters to return normalized data rather than sending raw
HTML to the model. A normalized problem object should include `platform`,
`problem_key`, `url`, `title`, contest/index identifiers, nullable `rating`,
official tags, statement text, provenance, source path, and `metadata_status`.
JSON is the transport format between extractors, Codex, and MCP; it is not a
replacement for normalized database columns or the raw transcript.

Platform rules:

- Codeforces accepts both `/contest/{id}/problem/{index}` and
  `/problemset/problem/{id}/{index}`. Prefer the official
  `problemset.problems` API for name, rating, and tags, and cache the response.
- AtCoder keys come from the contest/task slugs, for example `abc468_b`.
- CodeChef keys come from the final problem-code segment for both direct and
  practice-course URLs.
- CSES filenames use the official title, while keys use the stable numeric task
  ID from the URL.
- LeetCode filenames use the canonical `titleSlug`, while keys use the stable
  frontend problem ID. Convert slug hyphens to underscores only for the
  filename.

Programmatic HTML fetching and parsing is web scraping, even when no model is
involved. Prefer official APIs or stable structured endpoints; otherwise use a
small rate-limited parser that respects platform terms and caches results.
Never block reflection persistence on metadata failure. Save nullable metadata
with `metadata_status = pending` so it can be refreshed later.

## AI and API Boundary

For the Codex-native MVP, do not add an OpenAI or Gemini API call merely to
summarize the interview. Codex should conduct the interview, create the
structured summary, and call MCP in the same task. ChatGPT subscription billing
and OpenAI API billing are separate, so a Plus subscription must not be treated
as bundled API credit.

If a standalone web interviewer is later authorized, use one stateful Responses
API conversation for both the adaptive interview and final Structured Output.
Keep API keys server-side. Do not copy a ChatGPT UI transcript into a second API
product solely to obtain the summary.

## Testing Guidelines

There is no repository-wide test framework or coverage target. For every changed solution, compile with warnings enabled and test official samples. For nontrivial algorithms, add edge cases or run the folder's generator/brute-force stress setup. Confirm output exactly with `diff` (or `diff -w` only when whitespace is intentionally irrelevant).

When reflection integration exists, verify URL normalization, MCP tool
discovery, metadata-failure persistence, atomic/idempotent saves, transcript
preservation, and review-date handling. A warm save should target under 300 ms,
excluding optional metadata refresh.

## Commit & Pull Request Guidelines

Recent commits use short, imperative summaries such as `Solved 1855B.cpp`, `Add code for 1914A.cpp`, and `Edit template.cpp`. Keep each commit focused on one problem or one coherent template change.

Pull requests should list affected problem IDs, summarize the algorithm or template change, and include the exact compile/test commands run. Mention known assumptions, complexity, and any missing stress coverage.
