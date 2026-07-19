/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:18:02 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:33:35 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// op_sa: swap the two top elements of stack a
void	op_sa(t_data *d)
{
	t_stack	*first; // stores the original top node

	if (!d->a || !d->a->next) // if no second node
		return ;
	first = d->a; // save current top node
	d->a = first->next; // head points to second node
	first->next = d->a->next; // connect old first node to the node after
	d->a->next = first; // put the old first node after the new top
	if (!d->mute)
		ft_putstr_fd("sa\n", 1); // print op
	d->ops.sa++; // record sa for benchmarking
}

// op_sb: swap the two top elements of stack b
void	op_sb(t_data *d)
{
	t_stack	*first;

	if (!d->b || !d->b->next)
		return ;
	first = d->b;
	d->b = first->next;
	first->next = d->b->next;
	d->b->next = first;
	if (!d->mute)
		ft_putstr_fd("sb\n", 1);
	d->ops.sb++;
}

// op_ss: sa and sb at the same time
void	op_ss(t_data *d)
{
	t_stack	*first;

	if (d->a && d->a->next)
	{
		first = d->a;
		d->a = first->next;
		first->next = d->a->next;
		d->a->next = first;
	}
	if (d->b && d->b->next)
	{
		first = d->b;
		d->b = first->next;
		first->next = d->b->next;
		d->b->next = first;
	}
	if (!d->mute)
		ft_putstr_fd("ss\n", 1);
	d->ops.ss++;
}
