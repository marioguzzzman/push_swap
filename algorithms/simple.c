/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 14:13:05 by dbali             #+#    #+#             */
/*   Updated: 2026/07/07 16:23:42 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Insertion sort

#include <stdio.h>

void	insertion_sort(int arr[], int n)
{
	int	to_sort;
	int	i;
	int	j;

	i = 1;
	while (i < n)
	{
		to_sort = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j] > to_sort)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = to_sort;
		i++;
	}
}

int	main(void)
{
	int	n;
	int	i;

	int arr[6] = {20, 60, 50, 40, 30, 10};
	n = sizeof(arr) / sizeof(arr[0]);
	insertion_sort(arr, n);
	i = 0;
	while (i < n)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	return (0);
}
