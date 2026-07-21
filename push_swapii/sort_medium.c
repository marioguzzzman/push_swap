/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:04:09 by dbali             #+#    #+#             */
/*   Updated: 2026/07/16 17:10:07 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int_sqrt_ceil: smallest integer r such that r*r >= n (n >= 0)
static int	int_sqrt_ceil(int n)
{
	int	r;

	r = 0;
	while (r * r < n)
		r++;
	return (r);
}

/*
	chunk_of: returns which chunk a rank (node->rank) belongs to, given the
	chosen chunk_size. Chunk 0 holds the smallest values. This plain division
	only slices evenly because ranks are dense in [0, n-1]; the raw values are
	not, so the same division on values would be meaningless.
*/
static int	chunk_of(int rank, int chunk_size)
{
	return (rank / chunk_size);
}

/*
	count_chunk_members: how many elements currently in a belong to chunk c.
	Needed up-front so the scan-and-push loop below knows exactly how many
	matches to expect and can stop deterministically.
*/
static int	count_chunk_members(t_stack *a, int c, int chunk_size)
{
	int	count;

	count = 0;
	while (a)
	{
		if (chunk_of(a->rank, chunk_size) == c)
			count++;
		a = a->next;
	}
	return (count);
}

// medium_sort: O(n*sqrt(n)) chunk-based
void	medium_sort(t_data *d)
{
	int	n;
	int	num_chunks;
	int	chunk_size;
	int	c;
	int	target;
	int	processed;

	n = stack_size(d->a);
	if (n < 2)
		return ;
	num_chunks = int_sqrt_ceil(n);
	if (num_chunks < 1)
		num_chunks = 1;
	chunk_size = (n + num_chunks - 1) / num_chunks;
	c = 0;
	while (c < num_chunks)
	{
		target = count_chunk_members(d->a, c, chunk_size);
		processed = 0;
		while (processed < target)
		{
			if (chunk_of(d->a->rank, chunk_size) == c)
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
