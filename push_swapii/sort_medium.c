/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:04:09 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:05:15 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int_sqrt_ceil: how many buckets we need. For n numbers, we need sqrt(n) chunks.
// n = number of elements.
// if 100 nums, we need 10 buckets.
static int	int_sqrt_ceil(int n)
{
	int	r; // smallest num

	r = 0;
	while (r * r < n)
		r++;
	return (r);
}

/*
	chunk_of: returns which chunk a rank (node->index) belongs to, given the
	chosen chunk_size. Chunk 0 holds the smallest values.
*/
static int	chunk_of(int index, int chunk_size)
{
	return (index / chunk_size);
}

/*
	count_chunk_members: how many elements currently in a belong to a chunk.
*/
static int	count_chunk_members(t_stack *a, int c, int chunk_size)
{
	int	count;

	count = 0;
	while (a)
	{
		if (chunk_of(a->index, chunk_size) == c)
			count++;
		a = a->next;
	}
	return (count);
}

// medium_sort: O(n*sqrt(n)) chunk-based
void	medium_sort(t_data *d)
{
	int	n; // number of elements in a
	int	num_chunks; // number of chunks
	int	chunk_size; // how many indexes in one chunk
	int	c; // chunk no
	int	target; // how many indexes belong in the current chunk
	int	processed; // how many numbers from the current chunk have already been moved to b

	n = stack_size(d->a); // get stack size
	if (n < 2) // nothing to sort
		return ;
	num_chunks = int_sqrt_ceil(n); 
	if (num_chunks < 1) // div problems
		num_chunks = 1;
	chunk_size = (n + num_chunks - 1) / num_chunks;
	c = 0;
	while (c < num_chunks) // start at the smallest chunk
	{
		target = count_chunk_members(d->a, c, chunk_size); 
		processed = 0;
		while (processed < target) // find chunk members
		{
			if (chunk_of(d->a->index, chunk_size) == c) // is the top element part of this chunk
			{
				insert_sorted_b(d);
				processed++;
			}
			else
				op_ra(d);
		}
		c++;
	}
	while (d->b)
		op_pa(d);
}
