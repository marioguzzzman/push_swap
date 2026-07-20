/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:58:58 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 11:58:59 by dbali            ###   ########.fr       */
/*                                                                            */
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

// stack_add_top: pushes an already-allocated node onto the top of *stack
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
	top = *stack;
	*stack = (*stack)->next;
	top->next = NULL;
	return (top);
}

// free_stack: frees every node of *stack and resets it to NULL
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

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
	long	pivot;
	int		i;
	int		j;
	long	tmp;

	if (lo >= hi)
		return ;
	pivot = arr[(lo + hi) / 2];
	i = lo;
	j = hi;
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	sort_long_array(arr, lo, j);
	sort_long_array(arr, i, hi);
}

// binary_search: returns the index of value inside the sorted array
static int	binary_search(long *sorted, int n, long value)
{
	int	lo;
	int	hi;
	int	mid;

	lo = 0;
	hi = n - 1;
	while (lo <= hi)
	{
		mid = (lo + hi) / 2;
		if (sorted[mid] == value)
			return (mid);
		else if (sorted[mid] < value)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return (-1);
}

/*
	assign_indexes: gives every node of stack a its rank (0 = smallest value,
	size-1 = biggest value) in the node's ->index field
*/
void	assign_indexes(t_data *data)
{
	int		n;
	long	*values;
	t_stack	*node;
	int		i;

	n = stack_size(data->a);
	if (n == 0)
		return ;
	values = malloc(sizeof(long) * n);
	if (!values)
		exit_error(data);
	node = data->a;
	i = 0;
	while (node)
	{
		values[i++] = node->value;
		node = node->next;
	}
	sort_long_array(values, 0, n - 1);
	node = data->a;
	while (node)
	{
		node->index = binary_search(values, n, node->value);
		node = node->next;
	}
	free(values);
}

/*
	compute_disorder: implements the mandatory disorder metric from the
	subject exactly as specified (ratio of out-of-order pairs over all
	pairs), computed BEFORE any move is performed.
*/
double	compute_disorder(t_stack *stack)
{
	int		mistakes;
	long	total_pairs;
	t_stack	*i;
	t_stack	*j;

	mistakes = 0;
	total_pairs = 0;
	i = stack;
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
