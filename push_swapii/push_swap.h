#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/*
	t_stack: one node of a stack, implemented as a singly linked list.
		value - the number stored in this node (given by user).
		index - the position of this value inside the whole data set
	            (0 = smallest, size-1 = biggest).
		next - pointer to the next node (below the current one). The head of the list is always the TOP of the stack.
*/
typedef struct s_stack
{
	long				value;
	int					index;
	struct s_stack		*next;
}	t_stack;

/*
	t_opcount: the total of every push_swap operation completed,
	used only for the --bench report.
*/
typedef struct s_opcount
{
	int	sa; // Number of sa operations performed
	int	sb; // ...
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
	t_stack		*a; // Stack a
	t_stack		*b; // Stack b
	t_opcount	ops; // Counters of ops performed
	int			bench; // 1 if --bench passed, 0 otherwise
	int			mute; // 1 to silence normal op printing
	const char	*strategy; // Which algorithm was used
	const char	*complexity; // Hig O of that strategy 
	double		disorder; // Disorder 0-1
}	t_data;

// utils.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putnbr_fd(long n, int fd);
void	ft_putnbr_double_fd(double n, int fd); // For disorder
int		ft_str_is_number(const char *s); // For the string

// parsing.c - turns argv into a validated stack a
int		parse_arguments(int argc, char **argv, t_data *data); // Read argv/argc
int		ft_strncmp_local(const char *a, const char *b); // strcmp()

// stack.c - stack helpers
int		stack_size(t_stack *stack); // Counts stack nodes
void	stack_add_top(t_stack **stack, t_stack *new_node); // Insert at the top
t_stack	*stack_pop_top(t_stack **stack); // Remove the top
void	free_stack(t_stack **stack); // Free the stack
int		is_sorted(t_stack *stack); // 1 if stack is sorted, 0 otherwise
void	assign_indexes(t_data *data); // Goes through data->a and assigns index to each value
double	compute_disorder(t_stack *stack); // Calculate disorder

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
void	print_bench(t_data *d); // Summary report

// error.c
void	exit_error(t_data *data); // Printd "Error\n"

#endif
