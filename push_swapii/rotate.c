/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:19:24 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:33:41 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
// op_ra: rotate a up by one (top becomes the bottom)
void	op_ra(t_data *d)
{
	t_stack	*top; // original first node
	t_stack	*node;

	if (!d->a || !d->a->next)
		return ;
	top = stack_pop_top(&d->a); // remove 1st elem
	node = d->a; // start from the new top of a
	while (node->next) // find the next node
		node = node->next;
	node->next = top; // put last node at the top
	if (!d->mute)
		ft_putstr_fd("ra\n", 1);
	d->ops.ra++;
}

// op_rb: rotate b up by one (top becomes the bottom)
void	op_rb(t_data *d)
{
	t_stack	*top;
	t_stack	*node;

	if (!d->b || !d->b->next)
		return ;
	top = stack_pop_top(&d->b);
	node = d->b;
	while (node->next)
		node = node->next;
	node->next = top;
	if (!d->mute)
		ft_putstr_fd("rb\n", 1);
	d->ops.rb++;
}

// op_rr: ra and rb at the same time
void	op_rr(t_data *d)
{
	t_stack	*top;
	t_stack	*node;

	if (d->a && d->a->next)
	{
		top = stack_pop_top(&d->a);
		node = d->a;
		while (node->next)
			node = node->next;
		node->next = top;
	}
	if (d->b && d->b->next)
	{
		top = stack_pop_top(&d->b);
		node = d->b;
		while (node->next)
			node = node->next;
		node->next = top;
	}
	if (!d->mute)
		ft_putstr_fd("rr\n", 1);
	d->ops.rr++;
}
