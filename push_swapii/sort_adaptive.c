/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:06:59 by dbali             #+#    #+#             */
/*   Updated: 2026/07/16 17:09:49 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// adaptive_sort: chooses simple/medium/complex based on d->disorder
void	adaptive_sort(t_data *d)
{
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
		d->complexity = "O(n log n)";
		complex_sort(d);
	}
}
