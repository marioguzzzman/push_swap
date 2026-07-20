/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rank.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:58:58 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 17:34:33 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap_long(long *a, long *b)
{
	long	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
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
			swap_long(&arr[i], &arr[j]);
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
	stack_to_array(): Converts a stack to array 
	to assign indexes to each node without modifying 
	the original stack
*/
static long	*stack_to_array(t_data *data, int n)
{
	long	*values;
	t_stack	*node;
	int		i;

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
	return (values);
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

	n = stack_size(data->a);
	if (n == 0)
		return ;
	values = stack_to_array(data, n);
	sort_long_array(values, 0, n - 1);
	node = data->a;
	while (node)
	{
		node->index = binary_search(values, n, node->value);
		node = node->next;
	}
	free(values);
}
