/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sorted_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:13:35 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:33:53 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	insert_sorted_b(): 
	moves the CURRENT TOP of a onto b, 
	inserting it at the correct spot so that b stays sorted in DESCENDING order
		1. save the value at the top of a
		2. count how many values in b are greater than it
		3. rotate b until the insertion point reaches the top
		4. push the value from a to b
*/
void	insert_sorted_b(t_data *d)
{
	long	value; // the value to insert
	t_stack	*node;
	int		count_greater; // how many numbers are rgeater than value
	int		i;

	if (!d->a)
		return ;
	value = d->a->value; // save the value on top of a
	count_greater = 0;
	node = d->b; // scan b from its top
	while (node && node->value > value) // traverse b while current values are greates than the value to insert
	{
		count_greater++;
		node = node->next;
	}
	i = 0;
	while (i++ < count_greater) // rotate b 'count_greater' times
		op_rb(d); 
	op_pb(d); push the top element from a to b
	i = 0;
	while (i++ < count_greater) // reverse the rotations of b
		op_rrb(d);
}
