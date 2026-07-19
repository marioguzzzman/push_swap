/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:02:59 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:05:14 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* 
simple_sort: O(n^2) insertion-sort
Take everything from a, insert them in b in sorted order, push everything back in a.
*/
void	simple_sort(t_data *d)
{
	if (!d->a || !d->a->next)
		return ;
	while (d->a) // move from a to b
		insert_sorted_b(d);
	while (d->b) // move back from b to a
		op_pa(d);
}
