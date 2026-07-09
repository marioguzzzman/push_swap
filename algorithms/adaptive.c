/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 16:39:16 by dbali             #+#    #+#             */
/*   Updated: 2026/07/09 16:39:17 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(void)
{
	int		i;
	double	disorder;

	long arr[] = {20, 60, 50, 40, 30, 10};

	disorder = disorder_calculation(arr, 6);
	printf("disorder: %f\n", disorder);

	if (disorder < 0.2)
	{
		insertion_sort(arr, 6);
		printf("simple used\n");
	}
	else if (disorder >= 0.2 && disorder < 0.5)
	{
		bucket_sort(arr, 6);
		printf("medium used\n");
	}
	else
	{
		radix_sort(arr, 6);
		printf("complex used\n");
	}

	i = 0;
	while (i < 6)
	{
		printf("%ld ", arr[i]);
		i++;
	}
	printf("\n");
	return (0);
}
