/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:02:59 by dbali             #+#    #+#             */
/*   Updated: 2026/07/16 17:10:11 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// simple_sort: O(n^2) insertion-sort
void	simple_sort(t_data *d)
{
	if (!d->a || !d->a->next)
		return ;
	while (d->a)
		insert_sorted_b(d);
	while (d->b)
		op_pa(d);
}
