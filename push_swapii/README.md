*This activity has been created as part of the 42 curriculum by maguzman, dbali.*

# push_swap

## Description

`push_swap` sorts a list of integers held on stack `a` into ascending order
(smallest on top), using only the two stacks (`a` and `b`) and the eleven
moves defined by the Push_swap language: `sa`, `sb`, `ss`, `pa`, `pb`, `ra`,
`rb`, `rr`, `rra`, `rrb`, `rrr`. The program prints the exact sequence of
moves it used, one per line, on stdout.

The point of the project is algorithmic complexity: the same sorting problem
can be solved with wildly different numbers of operations depending on the
strategy used, so this implementation embeds **four** strategies with
different complexity classes and lets you pick one, or let the program pick
for you based on how disordered the input is.

## Instructions

```sh
make          # builds ./push_swap
make clean    # removes object files
make fclean   # removes everything
make re       # fclean + all
```

Examples:

```sh
$ ./push_swap 2 1 3 6 5 8
ra
pb
...

$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
OK

$ ./push_swap --bench 5 4 3 2 1 >/dev/null
--- push_swap benchmark ---
disorder: 100.00%
strategy: adaptive (complex) (O(n log n))
total operations: ...
```

Numbers can be passed either as separate arguments (`2 1 3`) or as one
quoted string (`"2 1 3"`). Invalid input (non-integer tokens, integers that
do not fit in an `int`, or duplicate values) makes the program print
`Error` on stderr and exit with a non-zero status without printing any
operation.

## Vocabulary

Three words in this codebase are easy to misread. They are defined here once
and used consistently everywhere else.

**Node vs. stack.** There is no stack *container* type in this program.
`t_stack` is a single **node** — a `value`, a `rank`, and a `next` pointer.
A *stack* is nothing more than a head pointer (`data->a`, `data->b`) aimed at
the top node of a chain. Pushing is two assignments (`new->next = *stack;
*stack = new`), popping is advancing the head pointer. A node is never copied
or reallocated when it moves between stacks — only which chain it hangs off
changes, which is why `pa`/`pb` are O(1). The helpers take `t_stack **`
precisely because they must reassign `data->a` itself, not just what it
points at.

**Primitive.** The word is used in two distinct senses:

- *Language primitives* — the eleven irreducible moves defined by the
  subject (`sa sb ss pa pb ra rb rr rra rrb rrr`), one function each in
  `swap.c`, `push.c`, `rotate.c`, `reverse_rotate.c`. Every line the program
  prints is one of these, and nothing decomposes them further.
- *Shared routine* — `insert_sorted_b`, built **out of** language
  primitives (`rb` × k, `pb`, `rrb` × k). It is a reusable building block
  for the strategy layer, not part of the instruction set.

**Rank** `node->rank` is where a value would sit **if the whole
input were sorted**: 0 = smallest, n-1 = biggest. It is decided by the value
alone and never changes once assigned.

Example:
`4 67 3 87 23`:

| stack position | value | rank |
| --- | --- | --- |
| 0 (top) | 4 | 1 |
| 1 | 67 | 3 |
| 2 | 3 | **0** |
| 3 | 87 | 4 |
| 4 (bottom) | 23 | 2 |

Position and rank are unrelated columns — the smallest value sits at
position 2. Reading the rank column top-to-bottom gives `1 3 0 4 2`, which
is scrambled: **assigning ranks sorts nothing.** `assign_ranks` writes a
field and never touches a single `next` pointer. The rank is a *label*
saying where a node belongs; the eleven operations are the only thing that
can physically move it there. Sorting is complete when the rank column reads
`0 1 2 3 4` from top to bottom.

## Architecture

The program is built in four layers. Each layer only depends on the ones
above it, which is why the four strategies share so much code.

**1. Stack model.** `t_stack` is a *node*, not a container: a singly
linked list where the head is always the TOP of the stack. `t_data` is the
single context struct passed to every function — it holds both stacks, the
per-operation counters, the flags and the disorder ratio. Because every
operation takes a `t_data *`, no global variable is needed and `--bench` accounting is free: each operation
increments its own counter as a side effect of performing the move.

**2. Rank substitution.** `assign_ranks` (`rank.c`) runs in three steps:
`stack_to_array` copies every node's value into a plain `long` array without
touching the stack, `sort_long_array` quicksorts that copy, and then, for
each node still on `a`, `binary_search` looks its value up in the sorted
copy — the position it lands on *is* the rank, written into `node->rank`.

*Why an array appears here at all.* `rank.c` is the only file in the project
that allocates an array, and it is pure scratch space — freed before
`assign_ranks` returns. It exists because binary search needs **O(1) random
access** (`sorted[mid]`), which a linked list cannot give: reaching the
middle of a list costs a walk. The linked list, conversely, is what makes
pushes and rotates O(1) pointer moves. So the two structures are used for
what each is good at: borrow an array for the one lookup-heavy step, write
the answers back into the nodes, discard the array. The *order* of the
stack is never modified by this layer.

*Why binary search rather than a linear scan.* The array is sorted, so each
comparison discards half the remaining candidates. Looking up `42` in
`[7, 19, 42, 88]`:

| step | lo | hi | mid | `sorted[mid]` | comparison | action |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 0 | 3 | 1 | 19 | 19 < 42 | `lo = mid + 1 = 2` |
| 2 | 2 | 3 | 2 | 42 | equal | return **2** |

Two comparisons instead of four; log₂(n) instead of n, so ~9 comparisons
per lookup at n=500 rather than 500. And because the array is sorted, the
position returned *is* the rank by definition.

Everything above this layer reasons about ranks only, never about raw
values. This substitution is what makes the
other three strategies expressible at all.

**3. Shared insertion primitive.** `insert_sorted_b` (`insert_sorted_b.c`)
moves the current top of `a` onto `b` and keeps `b` sorted descending. It
walks down `b` counting `count_greater`, the elements whose value is
still bigger than the incoming one, `rb`-rotates past exactly that many,
`pb`s the value into the gap that opens up right below them, then
`rrb`-rotates the same count back to restore `b`'s order. The cost of one
insertion is proportional to `count_greater`, not to `size(b)` — which is
why `--medium` visiting elements in chunk order (so `count_greater` never
exceeds the current chunk) is cheaper than `--simple` visiting them in
whatever order `a` happens to hold them. Two of the four strategies are
thin wrappers around this one routine — `--simple` is "call it n times,
then dump `b` back", and `--medium` is "call it n times, but visit the
elements in chunk order". The strategies are variations on a shared
routine, not four unrelated programs.

**4. Strategy dispatch.** `run_selected_strategy` in `main.c` selects an
algorithm from the command-line flag; with no flag it falls through to
`adaptive_sort`, which selects from the disorder ratio measured *before*
any move is performed, as the subject requires.

## Why ranks?

Rank substitution is not a convenience — `--medium` and `--complex` are not
expressible without it. The reason is a single property: ranks are **dense
and bounded**. They are exactly the integers `0..n-1`, with no gaps and
nothing larger than n. Raw values are neither.

**Chunks need density.** `chunk_of` (`sort_medium.c`) is plain integer
division: `rank / chunk_size`. With n=5, `num_chunks = ⌈√5⌉ = 3` and
`chunk_size = ⌈5/3⌉ = 2`, which slices the ranks into three consecutive
bands — ranks 0–1 → chunk 0, ranks 2–3 → chunk 1, rank 4 → chunk 2. Every
chunk is non-empty and the count is known in advance. Run the same division
on the raw values `4 67 3 87 23` and you get chunk numbers 2, 33, 1, 43, 11:
five elements scattered across 44 mostly-empty chunks. Division only slices
a set evenly when its members are packed into a known range.

**Radix passes need boundedness.** `complex_sort` reads one binary digit of
a rank at a time with `(rank >> bit) & 1` — `>> bit` shifts the wanted
column into last place, `& 1` keeps only that column, giving the yes/no
answer that splits the stack into two piles per pass. The number of passes
is the number of columns needed, `nb_bits(n) = ⌈log₂ n⌉`:

| rank | binary | bit 0 | bit 1 | bit 2 |
| --- | --- | --- | --- | --- |
| 0 | 000 | 0 | 0 | 0 |
| 1 | 001 | 1 | 0 | 0 |
| 2 | 010 | 0 | 1 | 0 |
| 3 | 011 | 1 | 1 | 0 |
| 4 | 100 | 0 | 0 | 1 |

Three columns label five elements. Run radix on raw values instead and the
pass count is set by the widest possible `int`, not by n: **31 passes
regardless of input size**, so 31·n operations for 5 elements as readily as
for 500. On ranks it is ⌈log₂ n⌉ — 3 passes at n=5, 9 at n=500. That
difference *is* the O(n log n) claim; without ranks the strategy would be
O(31n) with a constant nobody can defend as logarithmic.

## Algorithms

The mandatory disorder metric (ratio of out-of-order pairs over all pairs,
computed *before* any move) is used both to report `--bench` statistics and
to drive the adaptive strategy.

- **`--simple` (insertion sort, O(n²)).** Every element of `a` is pushed to
  `b` one at a time and immediately slid into its correct spot with the
  classic *rotate / push / rotate-back* trick, so `b` stays sorted
  descending (top = biggest) after every push. Finding the correct spot
  costs up to `size(b)` rotations, repeated `n` times → O(n²). Once `a` is
  empty, popping `b` back with plain `pa` calls rebuilds `a` ascending
  (the smallest value is the last one popped, so it ends on top).

- **`--medium` (chunk sort, O(n·√n)).** Ranks are split into
  `⌈√n⌉` chunks of `⌈√n⌉` values each. Chunks are processed from smallest
  to biggest; for each chunk, `a` is scanned (`ra` rotates past
  non-matching elements) and every matching element is inserted into `b`
  with the *same* rotate/push/rotate-back routine used by `--simple`.
  Because chunks are handled in increasing order, `b` is always fully
  sorted, so the "how many elements above me are bigger" scan always stops
  at the previous (smaller) chunk boundary — it never costs more than the
  current chunk's size (~√n). Scanning `a` costs O(n) per chunk over √n
  chunks, and insertion costs O(√n) per element over n elements: both
  O(n·√n).

  *Tradeoff* The rotate/push/rotate-back process
  pays a round trip: `rb` rotates past `count_greater` elements, `pb`
  inserts, then `rrb` rotates the same elements back making it 2×`count_greater`
  operations per insertion, not exactly `count_greater`. The restore is not
  optional: both the *next* insertion's scan (which assumes `b`'s head is
  the current maximum) and the final unwind (`pa` is called blindly, with
  no repositioning) depend on `b` staying sorted from the head
  after every call. If we skip the restore the rotated-away
  elements might be silently buried at the tail, corrupting the next lookup and
  the final output with no error raised. Measured at n=500 (5 random
  trials), this costs `--medium` ~11,300 operations on average against a
  12,000 "pass" ceiling, but with less margin than
  `--complex` leaves at the same n (~6,800).

- **`--complex` (LSD radix sort, O(n·log n)).** Treats each rank as a
  `⌈log2(n)⌉`-bit binary number and sorts it one bit at a time, from the
  least significant bit up: for every element currently in `a`, if the
  current bit is `1` it is sent to the back of `a` with `ra` (keeping its
  relative order among other "1" elements); if it is `0` it is pushed to
  `b`. After going through every element once, `b` is dumped back onto `a`
  with `pa`, which stably moves all the "0" elements back on top, ahead of
  the untouched "1" elements. After `⌈log2(n)⌉` passes, `a` is fully
  sorted. Each pass touches every element exactly once, so the total cost
  is O(n·log n).

- **`--adaptive` (default).** For n≤3, bypasses disorder entirely and uses
  a hardcoded decision tree (`sort_two`/`sort_three` in `sort_adaptive.c`). It only applies to the *default* path;
  `--simple`/`--medium`/`--complex` are left running their general
  algorithms even at tiny n.

  For n>3, picks a strategy from the disorder ratio of the *initial*
  stack:
  - `disorder < 0.2` → `sort_simple` (O(n²))
  - `0.2 ≤ disorder < 0.5` → `sort_medium` (O(n·√n))
  - `disorder ≥ 0.5` → `sort_complex` (O(n log n))

## Resources

- 42 project subject (`push_swap`), which specifies the stack operations,
  the disorder metric and the required complexity classes.
- General references on LSD radix sort and bucket sort used to design the
  stack-based adaptations above.

Radix: https://www.geeksforgeeks.org/dsa/radix-sort/

## Contributors

- `maguzman`: stack/operations core, parsing/validation, error handling, `--bench` reporting, norm fix, `--adaptive`'s n≤3 small-input path.
- `dbali`: stack/operations core, `--simple`, `--medium`, `--complex` and `--adaptive` strategies, parsing/validation, error handling, `--bench` reporting, testing.

## Use of AI
AI was used to explain in a simpler way some of theory behind the algorithms as well as a socratic teacher to explain parts of the code. 