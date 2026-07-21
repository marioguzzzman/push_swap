*This project has been created as part of the 42 curriculum by maguzman, dbali.*

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

$ ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./linux_checker $ARG
OK

$ ./push_swap --bench 5 4 3 2 1 >/dev/null
--- push_swap benchmark ---
disorder: 100.00%
strategy: complex (O(n log n))
total operations: ...
```

Numbers can be passed either as separate arguments (`2 1 3`) or as one
quoted string (`"2 1 3"`). Invalid input (non-integer tokens, integers that
do not fit in an `int`, or duplicate values) makes the program print
`Error` on stderr and exit with a non-zero status without printing any
operation.

## Architecture

The program is built in four layers. Each layer only depends on the ones
above it, which is why the four strategies share so much code.

**1. Stack model.** `t_stack` is a *node*, not a container: a singly
linked list where the head is always the TOP of the stack. `t_data` is the
single context struct passed to every function — it holds both stacks, the
per-operation counters, the flags and the disorder ratio. Because every
operation takes a `t_data *`, no global variable is needed and `--bench` accounting is free: each operation
increments its own counter as a side effect of performing the move.

**2. Rank substitution.** `assign_indexes` copies the values into a plain
array, sorts that array, and binary-searches each node's value back out of
it to obtain its **rank** (0 = smallest, n-1 = biggest), stored in
`node->index`. Everything above this layer reasons about ranks only, never
about raw values. This is the pivotal step: it turns "sort arbitrary
integers" into "sort a permutation of 0..n-1", which is exactly what makes
chunk boundaries and bitwise radix passes expressible in the first place.

**3. Shared insertion primitive.** `insert_sorted_b` moves the current
top of `a` onto `b` and keeps `b` sorted descending: it counts how many
elements at the top of `b` are greater than the incoming value, performs
that many `rb`, then `pb`, then rotates back with the same number of `rrb`.
Two of the four strategies are thin wrappers around it — `--simple` is
"call it n times, then dump `b` back", and `--medium` is "call it n times,
but visit the elements in chunk order". The strategies are variations on a
shared routine, not four unrelated programs.

**4. Strategy dispatch.** `run_selected_strategy` in `main.c` selects an
algorithm from the command-line flag; with no flag it falls through to
`adaptive_sort`, which selects from the disorder ratio measured *before*
any move is performed, as the subject requires.

## Algorithms

Every value is first converted to its **rank** (0 = smallest, n-1 =
biggest) so the algorithms only ever reason about small integers instead of
arbitrary values. The mandatory disorder metric (ratio of out-of-order
pairs over all pairs, computed *before* any move) is used both to report
`--bench` statistics and to drive the adaptive strategy.

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

- **`--adaptive` (default).** Picks a strategy from the disorder ratio of
  the *initial* stack:
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

- `maguzman`: stack/operations core, parsing/validation, error handling, `--bench` reporting.
- `dbali`:stack/operations core, `--simple`, `--medium`, `--complex` and `--adaptive` strategies,parsing/validation, error handling.`--bench` reporting, testing.

