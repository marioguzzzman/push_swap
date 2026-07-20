/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:18:02 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 12:05:31 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

// op_sa: swap the two top elements of stack a
void	op_sa(t_data *d)
{
	t_stack	*first;

	if (!d->a || !d->a->next)
		return ;
	first = d->a;
	d->a = first->next;
	first->next = d->a->next;
	d->a->next = first;
	if (!d->mute)
		ft_putstr_fd("sa\n", 1);
	d->ops.sa++;
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
