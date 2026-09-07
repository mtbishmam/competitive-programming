# Code index — peltorator

## Exact setup artifacts

| Path | Role |
|---|---|
| `artifacts/dotfiles/vim/.vimrc` | Full Vim/MacVim configuration linked by the 2021 video |
| `artifacts/snippets/cpp.snippets` | Full C++ UltiSnips file linked by the 2021 video |
| `sources/youtube/setup-video-transcript.txt` | Verbatim supplied 1,232-line transcript |
| `sources/youtube/video-description.md` | Complete live video description and links |
| `sources/youtube/setup-video-oembed.json` | YouTube title/channel metadata |

## All 32 C++ snippet triggers

| Trigger | Contents |
|---|---|
| `snips` | Comment listing available trigger names |
| `beg` | Full local-debug, EOF-loop contest template |
| `minimal` | Minimal header/namespace/`ll`/`main` template |
| `for` | Parameterized indexed loop |
| `read` | Read the first variable and return on EOF |
| `vect` | Vector declaration |
| `all` | Iterator pair for an entire container |
| `readvec` | Sized vector declaration and range input |
| `sort` | Sort an entire container |
| `pb` | `push_back` call |
| `graph` | Undirected graph input skeleton |
| `tree` | Undirected tree input skeleton |
| `rootedtree` | Parent-list rooted-tree input skeleton |
| `0rootedtree` | Root-at-zero tree input skeleton |
| `gcd` | Generic Euclidean GCD |
| `binpow` | Generic binary exponentiation |
| `inv` | Recursive modular inverse helper |
| `fft` | Complex-number FFT namespace and convolution support |
| `sufarr` | Suffix-array implementation |
| `aho` | Aho–Corasick automaton |
| `cht` | Convex hull trick line container |
| `segtree` | Customizable lazy segment tree skeleton |
| `centroid` | Centroid-decomposition skeleton |
| `sparse` | Generic sparse table |
| `decart` | Treap/Cartesian-tree implementation |
| `fenwick` | One-dimensional Fenwick tree |
| `Fenwick2D` | Two-dimensional Fenwick tree; trigger is case-sensitive |
| `modular` | Templated modular integer type |
| `table` | Four-direction grid offsets and boundary check |
| `{` | Brace block with cursor placed inside |
| `dsu` | Disjoint-set union |
| `deb` | `ONPC`-guarded debug-print framework |

The `snips` comment spells `fenwick2d` in lowercase, but the actual declaration
is `Fenwick2D`; the latter is the usable trigger. The video says some snippets
were outdated and identifies the FFT and segment tree as based on tourist's
code, so reuse requires review and provenance awareness.

## Original CP book

Snapshot: `sources/github/repos/peltorator-cp-book/` at commit
`db95b2288ab3d8e36c6a6c858959a01928418198`.

This Russian-language competitive-programming article collection has LaTeX,
website posts, diagrams, and selected code examples. Indexed topics include:

- Environment: fast I/O, randomization, and stress testing.
- Prefix/range queries: prefix sums, sparse tables, offline RMQ,
  Farach-Colton–Bender, down segment trees, Li Chao trees, and Segment Tree
  Beats.
- Dynamic programming/optimization: divide-and-conquer optimization, Knuth/Yao
  optimization, quadrangle inequality, lambda optimization, and persistent
  convex hull trick.
- Number theory: all modular inverses, discrete logarithm, highly composite
  numbers, Möbius convolution, modular factorial methods, powerful-number
  sieve, and modular square roots.
- Geometry: linear closest pair, two half-plane intersection approaches, and
  minimum enclosing circle.
- Algebra and trees: Hadamard transform and linear binary lifting.

The repository includes concrete C++ examples for random generation, stress
generation, divide-and-conquer/Knuth optimization, modular inverses/factorials,
prefix-sum variants, sparse tables, down segment trees, and basic Segment Tree
Beats.

## Segment Tree Beats study repository

Snapshot: `sources/github/repos/segment-tree-beats/` at commit
`7f2550abd7adf33e0f99b8d045879c52cc4ba50a`.

This repository accompanies Egor's bachelor thesis. Each family includes a
clean implementation, brute force, random/smart generators, test commands, and
in several cases intentionally wrong variants that demonstrate failed break or
tag conditions:

| Directory | Operations/lesson |
|---|---|
| `JiDriver-mineq-sum` | Range chmin and sum; alternative implementation and broken condition variants |
| `ExtendedJiDriver-mineq-pluseq-sum` | Range chmin, add, and sum |
| `GCDJiDriver-mineq-pluseq-GCD` | Chmin/chmax/assign/add plus sum/min/max/GCD queries and a GCD-heavy generator |
| `STB-sqrteq-sum` | Range add, square-root update, minimum, and sum; alternative and wrong tag conditions |
| `STB-diveq-sum` | Range add, division update, minimum, and sum; alternate conditions plus a divide-by-one performance trap |

The wrong solutions are research/test evidence and must not be copied as
templates.

## Forked reference collections

| Repository | Status | Scope |
|---|---|---|
| `algorithmica` | Fork | Multilingual algorithm-education site source |
| `cp-algorithms` | Fork | Broad algorithm/data-structure article collection |

These full snapshots are useful references, but fork status means their
contents cannot be attributed to Egor without file-level evidence.

## Adjacent research and profile repositories

| Repository | Relevance |
|---|---|
| `klees-measure-lower-bounds-repo` | Original checkers and constructions supporting research on Klee's Measure lower bounds; algorithmic research, not a contest template |
| `peltorator.github.io` | Current personal/academic site, identity evidence, publications, education, and bachelor-thesis PDF |
| `BOA-Project` | Listed original bi-objective search research project; not downloaded because it was classified outside the CP/setup archive boundary |

## Adjacent gist

`sources/github/gists/tinkoff-haskell-instructions/how_to_live.md` is a public
Russian-language Haskell-circle setup guide. It is educational context, not a
C++ competitive-programming template.
