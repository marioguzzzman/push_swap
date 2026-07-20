/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 11:58:58 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 15:32:13 by dbali            ###   ########.fr       */
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
