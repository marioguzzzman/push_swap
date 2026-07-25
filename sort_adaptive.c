/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   sort_adaptive.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/13 14:06:59 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/23 16:45:27 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_two(t_data *d)
{
	if (d->a->value > d->a->next->value)
		op_sa(d);
}

static void	sort_three(t_data *d)
{
	long	x0;
	long	x1;
	long	x2;

	x0 = d->a->value;
	x1 = d->a->next->value;
	x2 = d->a->next->next->value;
	if (x0 > x1)
		op_sa(d);
	if (x2 >= x0 && x2 >= x1)
		return ;
	if (x2 < x0 && x2 < x1)
		op_rra(d);
	else
	{
		op_rra(d);
		op_sa(d);
	}
}

static void	sort_small(t_data *d)
{
	int	n;

	n = stack_size(d->a);
	if (n == 2)
		sort_two(d);
	else if (n == 3)
		sort_three(d);
}

// adaptive_sort: chooses simple/medium/complex based on d->disorder

void	adaptive_sort(t_data *d)
{
	if (stack_size(d->a) <= 3)
	{
		d->strategy = "adaptive (small)";
		d->complexity = "O(1)";
		sort_small(d);
		return ;
	}
	if (d->disorder < 0.2)
	{
		d->strategy = "adaptive (simple)";
		d->complexity = "O(n^2)";
		simple_sort(d);
	}
	else if (d->disorder < 0.5)
	{
		d->strategy = "adaptive (medium)";
		d->complexity = "O(n*sqrt(n))";
		medium_sort(d);
	}
	else
	{
		d->strategy = "adaptive (complex)";
		d->complexity = "O(n*sqrt(n))";
		complex_sort(d);
	}
}
