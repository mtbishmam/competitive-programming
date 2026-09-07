# Code index — ecnerwala

## Current `cp-book` library

Snapshot: `sources/github/repos/cp-book/` at commit
`6d94fa04f139e11e71352fecbdc8de241fa038c3`.

This is Andrew's maintained C++23 reference library. Standalone headers live in
namespace `wala`; unit tests sit beside many headers, while `verify/` contains
Library Checker programs and CI metadata. The repository states that its code
is Andrew's unless a file says otherwise and notes inspiration from KACTL and
other references.

### Header map

| Area | Headers |
|---|---|
| General utilities | `bit_cast.hpp`, `hash_map.hpp`, `optimize.hpp`, `reverse_comparator.hpp`, `smawk.hpp`, `tensor.hpp`, `yc.hpp` |
| Combinatorial games | `combo_games/cold_games.hpp` |
| Data structures | `ds/bit.hpp`, `ds/cnt_min.hpp`, `ds/order_statistic.hpp`, `ds/rmq.hpp`, `ds/seg_tree.hpp` |
| FFT and formal power series | `fft/all.hpp`, `ap_sampled_poly.hpp`, `bm.hpp`, `common.hpp`, `core.hpp`, `engine.hpp`, `multiply.hpp`, `online.hpp`, `poly.hpp`, `series.hpp`, `series_core.hpp` |
| FFT engines | `fft/engines/algebras.hpp`, `crt.hpp`, `ntt.hpp`, `real.hpp`, `split.hpp` |
| Geometry | `geometry/point.hpp`, `point3d.hpp` |
| Graphs | `graph/make_st_dag.hpp`, `mcmf.hpp` |
| Linear algebra | `linalg/char_poly.hpp` |
| Number theory | `nt/dirichlet_series.hpp`, `jacobi.hpp`, `lattice_cnt.hpp` |
| Numeric types | `num/fraction.hpp`, `linear_fn.hpp`, `mat.hpp`, `modnum.hpp`, `nim_prod.hpp`, `pairnum.hpp`, `quaternion_hurwitz.hpp`, `trunc_series.hpp` |
| Sequences and strings | `seq/alphabetic_huffman_code.hpp`, `cartesian_tree.hpp`, `manacher.hpp`, `perm_tree.hpp`, `suffix_array.hpp` |
| Trees | `tree/lct.hpp`, `level_ancestor.hpp`, `static_tree.hpp`, `top_tree.hpp` |

`fft/test_util.test.hpp` is test-only and is intentionally excluded from the
library's exported header set.

### Verified problem families

The saved `verify/` programs cover Fenwick/segment-tree queries, static RMQ,
formal power series and convolution operations, geometry angle sorting,
st-numbering, characteristic polynomial, min-plus convolution, Dirichlet
series operations, nim product, Cartesian/common-interval decomposition trees,
palindromes, suffix arrays, substring counting, link-cut/top-tree operations,
level ancestor, LCA, and incremental minimum spanning forest.

### Library tooling

| Path | Role |
|---|---|
| `scripts/bundle.py` | Recursively bundles headers; supports minification and all-header generation |
| `scripts/make_verify.py` | Verification-support tooling |
| `.competitive-verifier/` | Competitive Verifier configuration |
| `CMakeLists.txt` | C++23 build, Catch2 tests, sanitizers, verification executables, optional coverage |
| `contest/` | Standalone problem creation, download, compile, run, and test system |

## Historical `icpc-book`

Snapshot: `sources/github/repos/icpc-book/` at commit
`f21d747074ee8fe2925adccd6e78ea7fbabb70b4`.

The repository itself marks this book unmaintained and points to KACTL or
`cp-book`. It remains valuable historical evidence. Its sections are:
combinatorial algorithms, contest setup, data structures, geometry, graph
algorithms, mathematics, number theory, numerical algorithms, strings, and
miscellaneous/various techniques. It includes the plugin-free contest Vim file,
GNU C++14 Makefile, contest template, hash helpers, troubleshooting notes, and
reference-book build system.

## Templates and contest tooling

| Path | Era and role |
|---|---|
| `sources/github/repos/cp-book/contest/template/__PROBLEM_NAME__.cpp` | Current minimal C++23 contest source |
| `sources/github/repos/cp-book/contest/template/Makefile` | Current sanitizer/PCH/run/diff workflow |
| `sources/github/repos/cp-book/contest/make_prob.py` | Current layered template instantiator |
| `sources/github/repos/cp-book/contest/download_prob.py` | Current stdlib Competitive Companion listener |
| `sources/github/repos/icpc-book/content/contest/template.cpp` | Historical GNU C++14/KACTL-style template |
| `sources/github/repos/icpc-book/content/contest/vimrc` | Historical plugin-free ICPC Vim setup |
| `sources/github/repos/cptemp/template.cpp` | Minimal 2015 C++11 template |
| `sources/github/repos/cptemp/Makefile` | 2015 warning/debug/sample workflow |
| `sources/github/gists/competitive-programming-makefile/Makefile` | Public evolving Makefile gist |
| `sources/github/gists/cp-template-system/` | Public layered template and problem downloader gist |

The archived `cvimrc` gist configures browser-style Vim navigation and is not a
C++ or ICPC Vim configuration.

## Solution and programming archives

| Repository | Contents and use |
|---|---|
| `contest-programming` | 7,019-file frozen solution archive covering Codeforces, ACM/ICPC, Code Jam, Distributed Code Jam, DMOJ, Hacker Cup, IOI, IPSC, POI, Project Euler, SPOJ, TopCoder, USACO, Polygon, and more; its own description says it is dead/unmaintained |
| `SPOJ` | Early SPOJ solutions, generators, samples, result files, and historical binaries |
| `TopCoder` | TopCoder templates/tooling artifacts |
| `traingate` | Training-gateway solutions |
| `aoc-2019` | Code from Andrew's Advent of Code 2019 speedrun |
| `synacor-challenge` | Synacor Challenge notebook and associated files |
| `CowCatcher` | Fork of the USACO 2014 Camp game |

Downloaded repository snapshots can contain old binaries and generated files.
They are evidence only and must not be executed.

## Related libraries and infrastructure

| Repository | Provenance | Relevance |
|---|---|---|
| `Num` | Original | Header-only arbitrary-precision integer and rational implementation |
| `competitive-verifier` | Fork | Verification framework used by the current CP book |
| `kactl` | Fork | Algorithm-reference source and historical successor/reference context |
| `testlib` | Fork | Contest checker/generator library |
| `cms` | Fork | Contest Management System infrastructure |

Forks are retained as reference context; their contents are not attributed to
Andrew unless a specific commit or file establishes authorship.
