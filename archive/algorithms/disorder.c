/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   disorder.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/09 14:43:49 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/09 16:02:32 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

double	disorder_calculation(long *arr_numbers, int numbers_len)
{
	int		total;
	double	disorder;
	int		mistakes;
	int		i;
	int		j;

	total = 0;
	mistakes = 0;
	i = 0;
	while (i < numbers_len - 1)
	{
		j = i + 1;
		while (j < numbers_len)
		{
			total++;
			if (arr_numbers[i] > arr_numbers[j])
			{
				mistakes++;
			}
			j++;
		}
		i++;
	}
	disorder = (double) mistakes / total;
	return (disorder);
}

// int	main(void)
// {
// 	long	arr[] =
// 	{
// 		2, 1, 5, 4, 3
// 	};
// 	printf("disorder: %f", disorder_calculation(arr, 5));
// }
