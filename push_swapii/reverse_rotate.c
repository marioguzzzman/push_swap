/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   reverse_rotate.c                                  :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/13 13:20:23 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/23 14:00:16 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

static void	reverse_rotate_stack(t_stack **stack)
{
	t_stack	*node;
	t_stack	*prev;

	if (!*stack || !(*stack)->next)
		return ;
	node = *stack;
	prev = NULL;
	while (node->next)
	{
		prev = node;
		node = node->next;
	}
	prev->next = NULL;
	node->next = *stack;
	*stack = node;
}

// op_rra: reverse rotate a (bottom becomes the top)

void	op_rra(t_data *d)
{
	reverse_rotate_stack(&d->a);
	if (!d->mute)
		ft_putstr_fd("rra\n", 1);
	d->ops.rra++;
}

// op_rrb: reverse rotate b (bottom becomes the top)

void	op_rrb(t_data *d)
{
	reverse_rotate_stack(&d->b);
	if (!d->mute)
		ft_putstr_fd("rrb\n", 1);
	d->ops.rrb++;
}

// op_rrr: rra and rrb at the same time

void	op_rrr(t_data *d)
{
	reverse_rotate_stack(&d->a);
	reverse_rotate_stack(&d->b);
	if (!d->mute)
		ft_putstr_fd("rrr\n", 1);
	d->ops.rrr++;
}
