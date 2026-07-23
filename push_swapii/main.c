/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/13 14:12:38 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/23 15:03:00 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
run_selected_strategy: dispatches on data->strategy (set either from a
command-line flag in parsing.c, or left at the "adaptive" default) and
records the human-readable strategy/complexity labels used by --bench.
Only "adaptive" needs to set these labels itself, since it decides the
actual algorithm at runtime based on the measured disorder.
*/

static void	run_selected_strategy(t_data *data)
{
	if (ft_strncmp_local(data->strategy, "simple") == 0)
	{
		data->complexity = "O(n^2)";
		simple_sort(data);
	}
	else if (ft_strncmp_local(data->strategy, "medium") == 0)
	{
		data->complexity = "O(n*sqrt(n))";
		medium_sort(data);
	}
	else if (ft_strncmp_local(data->strategy, "complex") == 0)
	{
		data->complexity = "O(n log n)";
		complex_sort(data);
	}
	else
		adaptive_sort(data);
}

/*
remove data.count_only elements
*/
int	main(int argc, char **argv)
{
	t_data	data;

	data.a = NULL;
	data.b = NULL;
	data.ops = (t_opcount)
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	data.bench = 0;
	data.mute = 0;
	data.count_only = 0;
	data.strategy = "adaptive";
	data.complexity = "";
	data.disorder = 0.0;
	if (!parse_arguments(argc, argv, &data))
		return (0);
	assign_ranks(&data);
	data.disorder = compute_disorder(data.a);
	if (is_sorted(data.a))
	{
		if (data.count_only)
			print_op_count(&data);
		if (data.bench)
		{
			data.strategy = "already sorted";
			data.complexity = "O(n)";
			print_bench(&data);
		}
		free_stack(&data.a);
		free_stack(&data.b);
		return (0);
	}
	run_selected_strategy(&data);
	if (data.count_only)
		print_op_count(&data);
	if (data.bench)
		print_bench(&data);
	free_stack(&data.a);
	free_stack(&data.b);
	return (0);
}
