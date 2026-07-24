/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:12:38 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/24 15:49:27 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	init_data(t_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->ops = (t_opcount){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	data->bench = 0;
	data->mute = 0;
	data->count_only = 0;
	data->strategy = "adaptive";
	data->complexity = "";
	data->disorder = 0.0;
}

static void	finalize(t_data *data)
{
	if (data->count_only)
		print_op_count(data);
	if (data->bench)
		print_bench(data);
	free_stack(&data->a);
	free_stack(&data->b);
}

int	main(int argc, char **argv)
{
	t_data	data;

	init_data(&data);
	if (!parse_arguments(argc, argv, &data))
		return (0);
	assign_ranks(&data);
	data.disorder = compute_disorder(data.a);
	if (is_sorted(data.a))
	{
		data.strategy = "already sorted";
		data.complexity = "O(n)";
		finalize(&data);
		return (0);
	}
	run_selected_strategy(&data);
	finalize(&data);
	return (0);
}
