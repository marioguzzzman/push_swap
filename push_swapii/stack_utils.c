/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:25:48 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 15:27:30 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
