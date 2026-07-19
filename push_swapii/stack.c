/* ************************************************************************** */
/*  stack.c                                                                   */
/*                                                                            */
/*  Generic linked-list helpers for t_stack (these are internal bookkeeping  */
/*  helpers, NOT Push_swap "operations" - they never print anything and are  */
/*  free to use as much as needed without affecting the operation count).    */
/*  Also provides assign_indexes (ranks every value from 0=smallest to       */
/*  n-1=biggest so the sorting algorithms can reason with integers) and      */
/*  compute_disorder (the mandatory disorder metric from the subject).       */
/* ************************************************************************** */

#include "push_swap.h"

// stack_size: number of nodes currently in the stack (0 if empty/NULL)
int	stack_size(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

// stack_add_top: pushes an already-allocated node onto the top of *tack
void	stack_add_top(t_stack **stack, t_stack *new_node)
{
	new_node->next = *stack;
	*stack = new_node;
}

// stack_pop_top:
// detaches and returns the top node of *stack (NULL if empty)
t_stack	*stack_pop_top(t_stack **stack)
{
	t_stack	*top;

	if (!stack || !*stack)
		return (NULL);
	top = *stack; // current top node
	*stack = (*stack)->next; // move the stack pointer to the next node
	top->next = NULL; // disconnect the removed node
	return (top);
}

// free_stack: frees every node of *stack and resets it to NULL
void	free_stack(t_stack **stack)
{
	t_stack	*tmp; // temp pointer to remember the next node before freeing the current 

	while (stack && *stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
}

// is_sorted: 1 if the stack is already sorted ascending top-to-bottom
int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
	sort_long_array: quicksort on a plain long array, used only
	to build the "which position does each value have"
*/
static void	sort_long_array(long *arr, int lo, int hi)
{
	long	pivot; // divides the array into two groups
	int		i; // mover forward looking for values too large
	int		j; // moves backward looking for values to small
	long	tmp; // temp for swapping two values

	if (lo >= hi)
		return ;
	pivot = arr[(lo + hi) / 2]; // the middle element
	i = lo;
	j = hi;
	while (i <= j) // continue until i and j cross
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) // if i and j have not crossed, the values are on the wrong side so swap them
		{
			tmp = arr[i]; // save arr[i]
			arr[i] = arr[j]; // move arr[j] into arr[i]
			arr[j] = tmp; // put the old arr[i] into arr[j]
			i++;
			j--;
		}
	}
	sort_long_array(arr, lo, j);
	sort_long_array(arr, i, hi);
}

/* 
	binary_search: returns the index of value inside the sorted array
		- sorted - sorted array
		- n - number of elems in the array
		- value - the number to find
*/
static int	binary_search(long *sorted, int n, long value)
{
	int	lo;
	int	hi;
	int	mid;

	lo = 0;
	hi = n - 1;
	while (lo <= hi)
	{
		mid = (lo + hi) / 2; // middle posiion
		if (sorted[mid] == value) // if found the value, return its index
			return (mid);
		else if (sorted[mid] < value) // if value > mid, search the other half
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return (-1); // if no value found
}

/*
	assign_indexes: gives every node of stack a its rank (0 = smallest value,
	size-1 = biggest value) in the node's ->index field
*/
void	assign_indexes(t_data *data)
{
	int		n; // number of nodes
	long	*values; // for stack values
	t_stack	*node; // pointer to walk through the linked list
	int		i;

	n = stack_size(data->a);
	if (n == 0) // if stack is empty
		return ;
	values = malloc(sizeof(long) * n); 
	if (!values)
		exit_error(data);
	node = data->a; // start at top
	i = 0;
	while (node) // fill the array
	{
		values[i++] = node->value;
		node = node->next;
	}
	sort_long_array(values, 0, n - 1); // sort the array
	node = data->a;
	while (node) // assign indexes
	{
		node->index = binary_search(values, n, node->value);
		node = node->next;
	}
	free(values);
}

// compute_disorder: calculate how unsorted a stack is
double	compute_disorder(t_stack *stack)
{
	int		mistakes; // when 1st > 2nd
	long	total_pairs;
	t_stack	*i; // 1st elem
	t_stack	*j; // 2nd elem

	mistakes = 0;
	total_pairs = 0;
	i = stack; // 1st node
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0)
		return (0);
	return ((double)mistakes / (double)total_pairs);
}
