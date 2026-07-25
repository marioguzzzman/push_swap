/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:05:50 by dbali             #+#    #+#             */
/*   Updated: 2026/07/24 14:05:00 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// nb_bits: how many bits are needed to represent every rank in [0, n-1]
static int	nb_bits(int n)
{
	int	bits;

	bits = 0;
	while ((1 << bits) < n)
		bits++;
	return (bits);
}

// sort_bit: process one bit position of the radix sort.
// Numbers with a 0 at this bit are pushed to stack b,
// while numbers with a 1 are rotated within stack a.
// Afterwards, all elements are moved back to stack a.
static void	sort_bit(t_data *d, int bit)
{
	int	count;
	int	i;

	count = stack_size(d->a);
	i = 0;
	while (i < count)
	{
		// check the value fo the current bit in the rank 
		if ((d->a->rank >> bit) & 1) // if bit is 1, rotate to bottom
			op_ra(d);
		else
			op_pb(d); // if bit is 0, push to b
		i++;
	}
	while (d->b) // push back in a
		op_pa(d);
}

// complex_sort: sort the stack using an LSD radix sort.
// Each pass processes one bit of the element ranks,
// from the least significant bit to the most significant.
void	complex_sort(t_data *d)
{
	int	n; // num of elems
	int	bits; // total num of bits
	int	bit; // current bit processing

	n = stack_size(d->a);
	if (n < 2)
		return ;
	bits = nb_bits(n);
	bit = 0;
	while (bit < bits)
	{
		sort_bit(d, bit);
		bit++;
	}
}
