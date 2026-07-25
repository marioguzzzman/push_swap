#!/bin/bash
# ====================================================================================
# push_swap tester - benchmark + error handling
# Edit PROG / CHECKER below if your binaries live elsewhere.
# ====================================================================================

PROG=./push_swap
CHECKER=./checker_linux

DEF='\033[0;39m'; RED='\033[1;91m'; GREEN='\033[1;92m'
YELLOW='\033[0;93m'; CYAN='\033[0;96m'

usage() {
	printf "${YELLOW}Usage:${DEF} ./ps_tester.sh [algo] [size] [runs] [disorder]\n\n"
	printf "  algo      simple | medium | complex | adaptive\n"
	printf "  size      list size                              (default 100)\n"
	printf "  runs      number of benchmark runs               (default 50)\n"
	printf "  disorder  target 0.0..1.0\n"
	printf "            omit for a plain random shuffle        (disorder ~0.5)\n\n"
	printf "Examples:\n"
	printf "  ./ps_tester.sh simple 100 50 0.19      # simple,   100 numbers, 50 runs, dis=0.19\n"
	printf "  ./ps_tester.sh medium 500 50           # medium,   500 numbers, 50 runs, shuf\n"
	printf "  ./ps_tester.sh complex 500 50          # complex,  500 numbers, 50 runs, shuf\n"
	printf "  ./ps_tester.sh adaptive 500 50 0.19    # adaptive, 500 numbers, 50 runs, dis=0.19\n"
}

if [ $# -eq 0 ] || [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
	usage
	exit 0
fi

ALGO="${1:-}"
SIZE="${2:-100}"
RUNS="${3:-50}"
DIS="${4:-}"
RANGE_MAX=$((SIZE * 100))

case "$ALGO" in
	simple|medium|complex|adaptive) ;;
	*) printf "${RED}invalid algo '%s' (use: simple|medium|complex|adaptive)${DEF}\n" \
		"$ALGO"; exit 1 ;;
esac
FLAG="--$ALGO"

if [ -n "$DIS" ]; then
	if ! echo "$DIS" | awk '{exit !($1+0==$1 && $1>=0 && $1<=1)}'; then
		printf "${RED}invalid disorder '%s' (use a number 0.0..1.0)${DEF}\n" "$DIS"
		exit 1
	fi
fi

[ -x "$PROG" ]    || { printf "${RED}push_swap not found: $PROG${DEF}\n"; exit 1; }
[ -x "$CHECKER" ] || { printf "${RED}checker not found: $CHECKER${DEF}\n"; exit 1; }

# Build a permutation of 0..n-1 with exactly K = round(D*n(n-1)/2) inversions,
# via a random Lehmer code (sum of codes == inversion count). Prints it space-
# separated. Disorder (fraction of inversions) of the result == D up to rounding.
gen_disorder() { # $1=n  $2=D  $3=seed
	awk -v n="$1" -v D="$2" -v seed="$3" 'BEGIN {
		srand(seed);
		total = n * (n - 1) / 2;
		k = int(D * total + 0.5);
		for (i = 0; i < n; i++) {
			maxh = n - 1 - i;
			rem = n - 2 - i;
			capafter = (rem < 0) ? 0 : rem * (rem + 1) / 2;
			lo = k - capafter; if (lo < 0) lo = 0;
			hi = maxh; if (hi > k) hi = k; if (hi < lo) hi = lo;
			L[i] = lo + int(rand() * (hi - lo + 1));
			if (L[i] > hi) L[i] = hi;
			k -= L[i];
		}
		for (i = 0; i < n; i++) avail[i] = i;
		m = n; out = "";
		for (i = 0; i < n; i++) {
			val = avail[L[i]];
			for (t = L[i]; t < m - 1; t++) avail[t] = avail[t + 1];
			m--;
			out = out val (i < n - 1 ? " " : "");
		}
		print out;
	}'
}

# Actual disorder of a sequence (fraction of inverted pairs), read from stdin.
calc_disorder() {
	awk '{
		n = NF;
		for (i = 0; i < n; i++) a[i] = $(i + 1);
		mistakes = 0;
		total_pairs = 0;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				total_pairs++;
				if (a[i] > a[j])
					mistakes++;
			}
		}
		printf "%.3f", (total_pairs > 0 ? mistakes / total_pairs : 0);
	}'
}

# ---- error handling (algo flag is irrelevant here, passed for consistency) -
err_pass=0; err_fail=0
check_error() {
	local desc="$1"; shift
	local out err
	out=$("$PROG" $FLAG "$@" 2>/tmp/ps_err.txt); err=$(cat /tmp/ps_err.txt)
	if [ -z "$out" ] && [ "$err" = "Error" ]; then
		err_pass=$((err_pass + 1))
	else
		err_fail=$((err_fail + 1))
		printf "${RED}[KO]${DEF} %-14s (stdout='%s' stderr='%s')\n" "$desc" "$out" "$err"
	fi
}

printf "${YELLOW}== Error handling ==${DEF}\n"
check_error "letters" "a";                 check_error "num+letters" "111a11"
check_error "two words" "hello world";     check_error "empty" ""
check_error "dup zero" "0" "0";            check_error "lead zeros" "-01" "-001"
check_error "glued neg" "111-1" "2" "-3";  check_error "dup neg" "-3" "-2" "-2"
check_error "INT_MIN-1" "-2147483649";     check_error "INT_MAX+1" "2147483648"
check_error "huge" "99999999999999999999"; check_error "lone minus" "-"
check_error "lone plus" "+";               check_error "double minus" "--1" "2"
check_error "double plus" "++1" "2";       check_error "dup" "42" "42"
check_error "dup in list" "1" "2" "3" "2"; check_error "junk" "4" "x" "3"
if [ $err_fail -eq 0 ]; then
	printf "${GREEN}error tests: %d/%d OK${DEF}\n" "$err_pass" "$err_pass"
else
	printf "${RED}error tests: %d OK, %d KO${DEF}\n" "$err_pass" "$err_fail"
fi

# ---- benchmark (live, one line per run) ------------------------------------
if [ -n "$DIS" ]; then
	src_desc=$(printf "disorder~%s" "$DIS")
else
	src_desc=$(printf "range=0..%d" "$RANGE_MAX")
fi
printf "\n${YELLOW}== Benchmark: algo=%s  N=%d  runs=%d  %s ==${DEF}\n" \
	"$ALGO" "$SIZE" "$RUNS" "$src_desc"

rm -f /tmp/ps_fails.txt
total=0; min=0; max=0; ko=0
for i in $(seq 1 "$RUNS"); do
	if [ -n "$DIS" ]; then
		arg=$(gen_disorder "$SIZE" "$DIS" "$RANDOM$i")
	else
		arg=$(shuf -i 0-"$RANGE_MAX" -n "$SIZE" | tr '\n' ' ')
	fi
	last_arg=$arg
	dis=$(printf "%s" "$arg" | calc_disorder)
	"$PROG" $FLAG $arg > /tmp/ps_ops.txt
	ops=$(wc -l < /tmp/ps_ops.txt)
	res=$("$CHECKER" $arg < /tmp/ps_ops.txt)
	total=$((total + ops))
	[ "$i" -eq 1 ] || [ "$ops" -lt "$min" ] && min=$ops
	[ "$ops" -gt "$max" ] && max=$ops
	if [ "$res" = "OK" ]; then
		printf "run %4d: %6d ops   ${GREEN}[%s]${DEF}   dis=%s   (running avg %s)\n" \
			"$i" "$ops" "$res" "$dis" "$(echo "scale=1; $total / $i" | bc)"
	else
		ko=$((ko + 1)); echo "$arg" >> /tmp/ps_fails.txt
		printf "run %4d: %6d ops   ${RED}[%s]${DEF}   dis=%s -> /tmp/ps_fails.txt\n" \
			"$i" "$ops" "$res" "$dis"
	fi
done
printf -- "---\n"
printf "Runs:    %d\n" "$RUNS"
printf "N:       %d\n" "$SIZE"
printf "Min:     %d\n" "$min"
printf "Max:     %d\n" "$max"
printf "Average: %s\n" "$(echo "scale=2; $total / $RUNS" | bc)"
if [ "$ko" -eq 0 ]; then
	printf "${GREEN}Sorting: %d/%d OK${DEF}\n" "$RUNS" "$RUNS"
else
	printf "${RED}Sorting: %d KO out of %d${DEF}\n" "$ko" "$RUNS"
fi

# ---- memory check (valgrind, same params as the benchmark) ------------------
printf "\n${YELLOW}== Valgrind leak check ==${DEF}\n"
if ! command -v valgrind >/dev/null 2>&1; then
	printf "${YELLOW}valgrind not installed, skipping${DEF}\n"
elif [ -z "$last_arg" ]; then
	printf "${YELLOW}no input generated, skipping${DEF}\n"
else
	printf "${CYAN}running: valgrind %s %s <%d numbers>${DEF}\n" \
		"$PROG" "$FLAG" "$SIZE"
	valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 \
		--errors-for-leak-kinds=all --track-origins=yes \
		--log-file=/tmp/ps_valgrind.txt \
		"$PROG" $FLAG $last_arg > /dev/null 2>&1
	vg_status=$?
	if [ "$vg_status" -eq 42 ]; then
		printf "${RED}valgrind: leaks/errors detected -> /tmp/ps_valgrind.txt${DEF}\n"
		grep -E "definitely lost|indirectly lost|possibly lost|ERROR SUMMARY" \
			/tmp/ps_valgrind.txt
	else
		printf "${GREEN}valgrind: no leaks, no errors${DEF}\n"
	fi
fi
