/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 13:18:50 by dbali             #+#    #+#             */
/*   Updated: 2026/07/20 12:07:21 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

// op_pa: move the top of b onto the top of a. Does nothing if b is empty
void	op_pa(t_data *d)
{
	t_stack	*node;

	if (!d->b)
		return ;
	node = stack_pop_top(&d->b);
	stack_add_top(&d->a, node);
	if (!d->mute)
		ft_putstr_fd("pa\n", 1);
	d->ops.pa++;
}

// op_pb: move the top of a onto the top of b. Does nothing if a is empty
void	op_pb(t_data *d)
{
	t_stack	*node;

	if (!d->a)
		return ;
	node = stack_pop_top(&d->a);
	stack_add_top(&d->b, node);
	if (!d->mute)
		ft_putstr_fd("pb\n", 1);
	d->ops.pb++;
}
