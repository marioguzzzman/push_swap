/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:20:23 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:33:46 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// op_rra: reverse rotate a (bottom becomes the top)
void	op_rra(t_data *d)
{
	t_stack	*node;
	t_stack	*prev; // prev node

	if (!d->a || !d->a->next)
		return ;
	node = d->a; // start at the top
	prev = NULL; // no prev yet
	while (node->next) // find the last node
	{
		prev = node;
		node = node->next;
	}
	prev->next = NULL; // disconnect the last node
	node->next = d->a; // attach the old last node before the current stack
	d->a = node; // update head
	if (!d->mute)
		ft_putstr_fd("rra\n", 1);
	d->ops.rra++;
}

// op_rrb: reverse rotate b (bottom becomes the top)
void	op_rrb(t_data *d)
{
	t_stack	*node;
	t_stack	*prev;

	if (!d->b || !d->b->next)
		return ;
	node = d->b;
	prev = NULL;
	while (node->next)
	{
		prev = node;
		node = node->next;
	}
	prev->next = NULL;
	node->next = d->b;
	d->b = node;
	if (!d->mute)
		ft_putstr_fd("rrb\n", 1);
	d->ops.rrb++;
}

// op_rrr: rra and rrb at the same time
void	op_rrr(t_data *d)
{
	t_stack	*node;
	t_stack	*prev;

	if (d->a && d->a->next)
	{
		node = d->a;
		prev = NULL;
		while (node->next)
		{
			prev = node;
			node = node->next;
		}
		prev->next = NULL;
		node->next = d->a;
		d->a = node;
	}
	if (d->b && d->b->next)
	{
		node = d->b;
		prev = NULL;
		while (node->next)
		{
			prev = node;
			node = node->next;
		}
		prev->next = NULL;
		node->next = d->b;
		d->b = node;
	}
	if (!d->mute)
		ft_putstr_fd("rrr\n", 1);
	d->ops.rrr++;
}
