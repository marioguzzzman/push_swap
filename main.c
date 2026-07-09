/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/03 17:44:15 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/09 17:46:56 by maguzman        ###   ########.fr        */
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
	char	*joined;
	char	*temp;
	t_stack	*a;
	t_stack	*b;

	i = 0;
	numbers_len = 0;
	if (argc == 1)
		return (1);
	if (argc == 2)
		arr_numbers = get_numbers(argv[1], &numbers_len);
	else
	{
		i = 1;
		joined = ft_strdup("");
		while (i < argc)
		{
			temp = joined;
			joined = ft_strjoin(joined, argv[i]);
			free(temp);
			temp = joined;
			joined = ft_strjoin(joined, " ");
			free(temp);
			i++;
		}
		arr_numbers = get_numbers(joined, &numbers_len);
		free(joined);
	}
	if (arr_numbers == NULL)
		return (1);
	a = init_stack();
	b = init_stack();
	i = 0;
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
