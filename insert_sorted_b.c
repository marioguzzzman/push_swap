/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sorted_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:13:35 by dbali             #+#    #+#             */
/*   Updated: 2026/07/16 18:13:06 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	insert_sorted_b(): 
	moves the CURRENT TOP of a onto b, 
	inserting it at the correct spot so that b stays sorted in DESCENDING order
*/
void	insert_sorted_b(t_data *d)
{
	long	value;
	t_stack	*node;
	int		count_greater;
	int		i;

	if (!d->a)
		return ;
	value = d->a->value;
	count_greater = 0;
	node = d->b;
	while (node && node->value > value)
	{
		count_greater++;
		node = node->next;
	}
	i = 0;
	while (i++ < count_greater)
		op_rb(d);
	op_pb(d);
	i = 0;
	while (i++ < count_greater)
		op_rrb(d);
}
