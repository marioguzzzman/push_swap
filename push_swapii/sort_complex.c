/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:05:50 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:06:16 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// nb_bits: how many bits are needed to represent every rank in [0, n-1]
static int	nb_bits(int n)
{
	int	bits;

	bits = 0;
	while ((1 << bits) < n) // 2^bits
		bits++;
	return (bits);
}

// complex_sort: O(n log n) LSD (least significant digit first) radix
void	complex_sort(t_data *d)
{
	int	n; // number of elements in stack a
	int	bits; // total no of binary passes
	int	bit; // current binary position we are checking
	int	i;
	int	count; // how many numbers are in a before starting one bit pass

	n = stack_size(d->a); // size of a
	if (n < 2)
		return ;
	bits = nb_bits(n); // how many digits required
	bit = 0;
	while (bit < bits) // start checking form the least significat bit
	{
		count = stack_size(d->a); // save current size
		i = 0;
		while (i < count)
		{

			// >> - bit shifting
			// & 1 - bit masking
			/*
				EXAMPLE (bit shifting):
				index = 5 / binary = 0101
				if bit=0, then 5>>0 => nothing moves
				if bit=1, then 5>>1 => move everything one position right: 0101 -> 0010 = 2
			*/

			/*
				EXAMPLE (bit masking) - 
				1 = 0001
				& means compare every bit and keep only positions where both are 1.
				index = 5 / binary = 0101
				compare:
					0101
				   &
				    0001
				   ------
				   	0001
				result = 1.

				Now, (5&1) return 1 => rotate a.
			*/
			if (((d->a->index >> bit) & 1) == 1) // check the current bit of the index
				op_ra(d);
			else
				op_pb(d);
			i++;
		}
		while (d->b) // put back into stack a
			op_pa(d);
		bit++;
	}
}
