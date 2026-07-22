/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 17:08:30 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/22 17:52:34 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
t_stack: one node of a stack, implemented as a singly linked list.
value - the number stored in this node.
rank - where this value would sit if the WHOLE input were sorted
(0 = smallest, size-1 = biggest). This is NOT the node's
position in the stack: it is decided by the value alone and
never changes once assigned. It lets every algorithm reason
about ordering using dense integers in [0, size-1] instead of
comparing arbitrary raw values everywhere.
next - pointer to the node underneath this one (towards the bottom of
the stack). The head of the list is always the TOP of the stack.
*/
typedef struct s_stack
{
	long			value;
	int				rank;
	struct s_stack	*next;
}	t_stack;

/*
t_opcount: keeps a running total of every push_swap operation completed,
used only for the --bench report.
*/
typedef struct s_opcount
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_opcount;

/*
t_data: the single "context" structure passed around the program.
a, b - the two stacks.
ops - operation counters, updated by every function in
/operations every time it actually performs a move.
bench - 1 if the --bench flag was included.
strategy - the strategy that was used (s, m, c, or a).
complexity - human readable complexity class of that strategy.
disorder - disorder ratio of the initial stack a, in [0, 1].
*/
typedef struct s_data
{
	t_stack		*a;
	t_stack		*b;
	t_opcount	ops;
	int			bench;
	int			mute;
	const char	*strategy;
	const char	*complexity;
	double		disorder;
}	t_data;

// utils.c
int		ft_isspace(int c);
void	put_str_fd(const char *s, int fd);
void	ft_putnbr_double_fd(double n, int fd);
int		ft_str_is_number(const char *s);

// parsing.c - turns argv into a validated stack a
int		is_flag(const char *arg, t_data *data);
int		parse_arguments(int argc, char **argv, t_data *data);
int		ft_strncmp_local(const char *a, const char *b);
int		has_duplicate(long *values, int n);
int		build_stack_from_values(t_data *data, long *values, int n);
char	**split_whitespace(const char *s);
long	token_to_long(const char *s, int *ok);
int		count_tokens(const char *s);
char	**split_needed(int *n, char **tokens);
char	**collect_tokens(int *n, int argc, char **argv, t_data *data);
int		validate(int n, long *values, char **tokens);

// stack.c - stack helpers
int		stack_size(t_stack *stack);
void	stack_add_top(t_stack **stack, t_stack *new_node);
t_stack	*stack_pop_top(t_stack **stack);
void	free_stack(t_stack **stack);
int		is_sorted(t_stack *stack);
void	assign_ranks(t_data *data);
double	compute_disorder(t_stack *stack);

// operations
void	op_sa(t_data *d);
void	op_sb(t_data *d);
void	op_ss(t_data *d);
void	op_pa(t_data *d);
void	op_pb(t_data *d);
void	op_ra(t_data *d);
void	op_rb(t_data *d);
void	op_rr(t_data *d);
void	op_rra(t_data *d);
void	op_rrb(t_data *d);
void	op_rrr(t_data *d);
void	insert_sorted_b(t_data *d);

// sort_simple.c - O(n^2) insertion sort adaptation
void	simple_sort(t_data *d);

// sort_medium.c - O(n * sqrt(n)) bucket sort
void	medium_sort(t_data *d);

// sort_complex.c - O(n log n) radix sort (LSD)
void	complex_sort(t_data *d);

// sort_adaptive.c - picks simple/medium/complex from disorder
void	adaptive_sort(t_data *d);

// bench.c - --bench report
void	print_bench(t_data *d);

// error.c
void	exit_error(t_data *data);

#endif
