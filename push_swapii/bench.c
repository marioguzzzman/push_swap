/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:09:38 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:10:49 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// total_ops: sums every counter in d->ops into the grand total
static int	total_ops(t_opcount *ops)
{
	return (ops->sa + ops->sb + ops->ss + ops->pa + ops->pb
		+ ops->ra + ops->rb + ops->rr + ops->rra + ops->rrb + ops->rrr);
}

// print_op_line: helper to print "   name: count\n" to stderr
static void	print_op_line(const char *name, int count)
{
	ft_putstr_fd("  ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd("\n", 2);
}

/*
	print_bench: prints the disorder percentage, the strategy
	name and its complexity class, the total operation count, and the
	per-operation-type breakdown.
*/
void	print_bench(t_data *d)
{
	ft_putstr_fd("--- push_swap benchmark ---\n", 2);
	ft_putstr_fd("disorder: ", 2);
	ft_putnbr_double_fd(d->disorder * 100.0, 2);
	ft_putstr_fd("%\n", 2);
	ft_putstr_fd("strategy: ", 2);
	ft_putstr_fd(d->strategy, 2);
	ft_putstr_fd(" (", 2);
	ft_putstr_fd(d->complexity, 2);
	ft_putstr_fd(")\n", 2);
	ft_putstr_fd("total operations: ", 2);
	ft_putnbr_fd(total_ops(&d->ops), 2);
	ft_putstr_fd("\n", 2);
	print_op_line("sa", d->ops.sa);
	print_op_line("sb", d->ops.sb);
	print_op_line("ss", d->ops.ss);
	print_op_line("pa", d->ops.pa);
	print_op_line("pb", d->ops.pb);
	print_op_line("ra", d->ops.ra);
	print_op_line("rb", d->ops.rb);
	print_op_line("rr", d->ops.rr);
	print_op_line("rra", d->ops.rra);
	print_op_line("rrb", d->ops.rrb);
	print_op_line("rrr", d->ops.rrr);
}