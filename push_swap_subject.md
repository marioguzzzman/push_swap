# Push_swap
*Because Swap_push doesn't feel as natural*

**Summary:** Sort data on a stack, with a limited set of instructions, using the lowest possible number of actions. Requires manipulating various algorithms and choosing the most appropriate one for optimized data sorting.

**⚠️ Group activity — must be completed by exactly 2 learners.**

Version: 1.1

---

## Table of Contents

1. [Group Project Requirements](#group-project-requirements)
2. [The Rules](#the-rules)
3. [Algorithm Requirements](#algorithm-requirements)
4. [Example](#example)
5. [The push_swap Program](#the-push_swap-program)
6. [Performance Benchmark](#performance-benchmark)
7. [Readme Requirements](#readme-requirements)
8. [Bonus Part — Checker](#bonus-part--checker)
9. [Submission & Peer Evaluation](#submission--peer-evaluation)

---

## Common Instructions (all 42 projects)

- Must be written in **C**, in accordance with **the Norm** (bonus files/functions included in norm check — one norm error = 0).
- No unexpected crashes (segfault, bus error, double free, etc.), except for undefined behavior — otherwise the project is non-functional and scores 0.
- All heap-allocated memory must be properly freed. **No memory leaks tolerated.**
- Makefile must compile with `-Wall -Wextra -Werror` using `cc`, and must **not** perform unnecessary relinking.
- Makefile must contain at least: `$(NAME)`, `all`, `clean`, `fclean`, `re`.
- Bonus submissions need a `bonus` rule in the Makefile; bonus code goes in `*_bonus.{c/h}` files. Mandatory and bonus are evaluated separately.
- If libft is allowed, copy its sources + Makefile into a `libft` folder; the project Makefile compiles libft first, then the project.
- Only work committed to the assigned Git repository is graded.

---

## Group Project Requirements

- **Exactly 2 learners**, both contributing meaningfully and understanding **all** implemented algorithms.
- `README.md` must clearly document both learners' contributions.
- Both learners must be present at defense and able to explain **any** part of the code.
- Both logins must appear in the repository submission.

---

## The Rules

- Two stacks: `a` and `b`.
- **Initial state:** `a` holds a random amount of unique negative/positive integers; `b` is empty.
- **Goal:** sort `a` in ascending order using only the allowed operations.

### Allowed Operations

| Op | Name | Effect |
|---|---|---|
| `sa` | swap a | Swap the top two elements of `a`. No-op if ≤1 element. |
| `sb` | swap b | Swap the top two elements of `b`. No-op if ≤1 element. |
| `ss` | swap both | `sa` and `sb` simultaneously. |
| `pa` | push a | Move top of `b` to top of `a`. No-op if `b` empty. |
| `pb` | push b | Move top of `a` to top of `b`. No-op if `a` empty. |
| `ra` | rotate a | Shift `a` up by one; first element becomes last. |
| `rb` | rotate b | Shift `b` up by one; first element becomes last. |
| `rr` | rotate both | `ra` and `rb` simultaneously. |
| `rra` | reverse rotate a | Shift `a` down by one; last element becomes first. |
| `rrb` | reverse rotate b | Shift `b` down by one; last element becomes first. |
| `rrr` | reverse rotate both | `rra` and `rrb` simultaneously. |

## Examples

`rra` Stack a, top to bottom: 1 2 3 4 (top=1, bottom=4). New order, top to bottom: 4 1 2 3
rra = "last becomes first, everything else shifts down by one":

---

## Algorithm Requirements

Must implement **four distinct sorting strategies**, selectable at runtime based on input.

### Complexity Model

- Strategies generate sequences of push_swap operations (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`).
- Complexity is measured in **number of push_swap operations generated**, not classical array-algorithm complexity.

### Disorder Metric (mandatory)

A number in `[0, 1]` describing how far `a` is from sorted. 0 = already sorted, 1 = worst possible order. Computed by counting inversions (pairs where a bigger number precedes a smaller one) over total pairs:

```
function compute_disorder(stack a):
    mistakes = 0
    total_pairs = 0
    for i from 0 to size(a)-1:
        for j from i+1 to size(a)-1:
            total_pairs += 1
            if a[i] > a[j]:
                mistakes += 1
    return mistakes / total_pairs
```

**Must be measured before any moves.**

### Required Strategies

1. **Simple — O(n²)**
   Examples: insertion sort adaptation, selection sort adaptation, bubble sort adaptation, simple min/max extraction.

2. **Medium — O(n√n)**
   Examples: chunk-based sorting (√n chunks), block-based partitioning, bucket sort with √n buckets, range-based sorting.

3. **Complex — O(n log n)**
   Examples: radix sort (LSD/MSD), merge sort adaptation with two stacks, quicksort with stack partitioning, heap sort, binary indexed tree approaches.

4. **Custom adaptive (your design)**
   Selects internal method based on measured disorder. Internal technique is your choice, but must respect complexity targets per regime:

   | Disorder | Required complexity |
   |---|---|
   | `< 0.2` (low) | O(n²) |
   | `0.2 ≤ disorder < 0.5` (medium) | O(n√n) |
   | `≥ 0.5` (high) | O(n log n) |

   Must document in `README.md`: threshold rationale, internal techniques per regime, and a brief complexity argument (time + space, upper bounds) within the push_swap model.

---

## Example

Starting stack `a`: `2 1 3 6 5 8` (both stacks grow from the right)

```
Init:        a: 2 1 3 6 5 8       b: (empty)
Exec sa:     a: 1 2 3 6 5 8       b: (empty)
Exec pb pb pb: a: 6 5 8           b: 3 2 1 (top→bottom: 3,2,1 shown as "6 3 / 5 2 / 8 1" pairs pushed)
Exec ra rb (= rr)
Exec rra rrb (= rrr)
Exec sa
Exec pa pa pa: a: 1 2 3 5 6 8     b: (empty)
```

Sorted in **12 operations**. Target: can you do better?

---

## The `push_swap` Program

| Field | Value |
|---|---|
| Program name | `push_swap` |
| Files to submit | `Makefile`, `*.h`, `*.c` |
| Makefile rules | `NAME`, `all`, `clean`, `fclean`, `re` |
| Arguments | stack `a` as a list of integers |
| External functions | `read`, `write`, `malloc`, `free`, `exit`, `ft_printf` (or your own equivalent) |
| Libft authorized | Yes |
| Description | Sort stacks |

### Rules

- Makefile must not relink.
- **Global variables are forbidden.**
- Program takes:
  - Stack `a` as a list of integers (first argument = top of stack).
  - An optional **strategy selector**:
    - `--simple` → force O(n²)
    - `--medium` → force O(n√n)
    - `--complex` → force O(n log n)
    - `--adaptive` → force adaptive (**default if no selector given**)
- Output: smallest possible list of operations to sort `a`, one per line (`\n`-separated, nothing else), smallest number ends up at top.
- Complexity class claimed per algorithm must be valid in this model.
- Strategy selection must work for **all valid inputs**, regardless of size/disorder.
- **No arguments** → no output, just return the prompt.
- **Error** → print `"Error"` + `\n` to **stderr**. Errors include: non-integer arguments, out-of-range integers, duplicate values.
- Binary must embed all four strategies; strategy name + complexity class must be reportable via `--bench`.

### Benchmark Mode (`--bench`)

Prints to **stderr** only (stdout keeps just the operations):
- Computed disorder (% with two decimals)
- Strategy used + theoretical complexity class
- Total operation count
- Per-operation-type counts (`sa`, `sb`, `ss`, `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`)

### Usage Examples

```sh
$ ./push_swap 2 1 3 6 5 8
ra
pb
rra
pb
pb
ra
pb
ra
pb
pb
pa
pa
pa
pa
pa
pa

# Default is --adaptive
$ ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
13

# Force simple O(n^2)
$ ./push_swap --simple 5 4 3 2 1
rra
pb
rra
pb
rra
pb
ra
pb
pb
pa
pa
pa
pa
pa

# Force complex O(n log n), verify with checker
$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK

# Large input
$ shuf -i 0-9999 -n 500 > args.txt; ./push_swap $(cat args.txt) | wc -l
6784

# Benchmark mode: hide ops, show metrics only
$ shuf -i 0-9999 -n 500 > args.txt
$ ./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
OK
$ cat bench.txt
[bench] disorder: 49.93%
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 7997
[bench] sa: 0 sb: 0 ss: 0 pa: 500 pb: 500
[bench] ra: 4840 rb: 1098 rr: 0 rra: 0 rrb: 1059 rrr: 0

# Combine bench + explicit strategy
$ ARG="4 67 3 87 23"; ./push_swap --bench --adaptive $ARG 2> bench.txt | ./checker_linux $ARG
OK
$ cat bench.txt
[bench] disorder: 40.00%
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 13
[bench] sa: 0 sb: 0 ss: 0 pa: 5 pb: 5
[bench] ra: 2 rb: 1 rr: 0 rra: 0 rrb: 0 rrr: 0

# Error handling
$ ./push_swap --adaptive 0 one 2 3
Error
$ ./push_swap --simple 3 2 3
Error
```

---

## Performance Benchmark

| Input size | Pass | Good | Excellent |
|---|---|---|---|
| 100 random numbers | < 2000 ops | < 1500 ops | < 700 ops |
| 500 random numbers | < 12000 ops | < 8000 ops | < 5500 ops |

Verified during evaluation with the provided checker.

---

## Readme Requirements

`README.md` at repo root, must include at minimum:

- **First line**, italicized: *This project has been created as part of the 42 curriculum by \<login1\>[, \<login2\>[, ...]].*
- **Description** — goal + brief overview.
- **Instructions** — compilation, installation, execution.
- **Resources** — classic references (docs, articles, tutorials) **and** how AI was used (which tasks, which parts).
- **Algorithm justification** — detailed explanation and justification of the chosen algorithms (required addition for this project).
- Additional sections as needed (usage examples, feature list, technical choices, etc.)

English recommended, or the main language of your campus.

---

## Bonus Part — Checker

> ⚠️ Bonus is only evaluated if the mandatory part is **perfect** — fully complete, no errors, all benchmarks validated without exception.

| Field | Value |
|---|---|
| Program name | `checker` |
| Files to submit | `*.h`, `*.c` |
| Makefile rule | `bonus` |
| Arguments | stack `a` as a list of integers |
| External functions | `read`, `write`, `malloc`, `free`, `exit`, `ft_printf` (or equivalent) |
| Libft authorized | Yes |
| Description | Execute the sorting operations |

### Behavior

- Takes stack `a` as argument (first arg = top of stack). No argument → no output.
- Reads operations from **stdin**, one per line (`\n`-terminated), until EOF, then executes them on `a`.
- If `a` ends up sorted **and** `b` is empty → print `"OK"` + `\n` to stdout.
- Otherwise → print `"KO"` + `\n` to stdout.
- On error (non-integer args, out-of-range, duplicates, unknown/malformed instruction) → print `"Error"` + `\n` to **stderr**.

```sh
$ ./checker 3 2 1 0
rra
pb
sa
rra
pa
OK

$ ./checker 3 2 1 0
sa
rra
pb
KO

$ ./checker 3 2 one 0
Error

$ ./checker "" 1
Error
```

You don't need to reproduce the exact reference binary's behavior — error handling is mandatory, but argument parsing strategy is up to you.

---

## Submission & Peer Evaluation

- Only work in the Git repo is evaluated. Double-check filenames.
- **Group requirements:** both learners listed as contributors; `README.md` documents both contributions; both present at defense; both able to explain/defend any part of the code.
- Evaluation may include a **live modification request** — a small behavior change, a few lines to write/rewrite, or an easy feature add — to verify real understanding. Scope and timing are set by the evaluation guidelines and can vary between defenses.

---

## AI Instructions (42 policy — for reference)

- Use AI to cut repetitive/tedious work, build prompting skill, and understand how AI systems work (risks, biases, ethics) — not to replace your own understanding.
- Only use AI-generated content you **fully understand and can take responsibility for**.
- Reflect on the problem *before* prompting. Systematically check, question, and test anything AI produces. Always seek peer review — AI lacks your specific context; peers don't.

**Good practice:** ask AI a scoped question ("how do I test a sorting function?"), try it, refine with a peer.
**Bad practice:** ask AI to generate a whole function, paste it in, and be unable to explain it at defense — this fails the project.
