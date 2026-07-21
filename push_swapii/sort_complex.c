/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:05:50 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 16:57:18 by maguzman         ###   ########.fr       */
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

// complex_sort: O(n log n) LSD radix
void	complex_sort(t_data *d)
{
	int	n;
	int	bits;
	int	bit;
	int	i;
	int	count;

	n = stack_size(d->a);
	if (n < 2)
		return ;
	bits = nb_bits(n);
	bit = 0;
	while (bit < bits)
	{
		count = stack_size(d->a);
		i = 0;
		while (i < count)
		{
			if (((d->a->rank >> bit) & 1) == 1)
				op_ra(d);
			else
				op_pb(d);
			i++;
		}
		while (d->b)
			op_pa(d);
		bit++;
	}
}
