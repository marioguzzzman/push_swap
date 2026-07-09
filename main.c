/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:44:15 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/09 19:38:27 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	long	*arr_numbers;
	int		numbers_len;
	t_stack	*a;
	t_stack	*b;

	i = 0;
	numbers_len = 0;
	if (argc == 1)
		return (1);
	arr_numbers = parse_args(argc, argv, &numbers_len);
	if (arr_numbers == NULL)
		write(2, "Error\n", 6);
	a = init_stack();
	b = init_stack();
	while (i < numbers_len)
	{
		stack_add_bottom(a, create_node(arr_numbers[i]));
		i++;
	}
	disorder_calculation(arr_numbers, numbers_len);
	free(arr_numbers);
	free(a);
	free(b);
	return (0);
}
