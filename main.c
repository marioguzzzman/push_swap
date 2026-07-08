/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:44:15 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/08 17:54:10 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	char	**arr_numbers;
	int		*numbers_len;
	t_stack	*a;
	t_stack	*b;

	i = 1;
	numbers_len = 0;
	if (argc > 1)
	{
		while (i < argc)
		{
			arr_numbers = get_numbers(argv[i], &numbers_len);
			i++;
		}
		if (arr_numbers == NULL)
			return (NULL);
		init_stack(&a);
		init_stack(&b);
	}
	else
		return (1);
	return (0);
}
