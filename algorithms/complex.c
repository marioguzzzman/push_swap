/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 15:49:16 by dbali             #+#    #+#             */
/*   Updated: 2026/07/08 16:14:13 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	radix_sort(int arr[], int n)
{
	int	max; // Biggest value in the array
	int	digit_place; // Current digit position
	int	bucket_count; // Number of buckets (10)
	int	**buckets; // Array of buckets
	int	*sizes; // How many elemens are in each bucket
	int	i;
	int	j;
	int	k;
	int	index; // Bucket number where the element is supposed to go

	// Find maximum value
	max = arr[0];
	i = 1;
	while (i < n)
	{
		if (arr[i] > max)
			max = arr[i];
		i++;
	}

	bucket_count = 10;

	// Allocate memory for buckets
	buckets = malloc(bucket_count * sizeof(int *));
	sizes = calloc(bucket_count, sizeof(int));

	i = 0;
	while (i < bucket_count)
	{
		buckets[i] = malloc(n * sizeof(int));
		i++;
	}

	digit_place = 1;

	while (max / digit_place > 0)
	{
		// Reset bucket sizes
		i = 0;
		while (i < bucket_count)
		{
			sizes[i] = 0;
			i++;
		}

		// Distribute elements into buckets
        /*
            number = 123
            digit_place = 1
            index = (123 / 1) % 10 = 3 ==> BUCKET 3

            digit_place = 10
            index = 2 ==> BUCKET 2

            digit_place = 100
            index = 1 ==> BUCKET 1
        */
		i = 0;
		while (i < n)
		{
			index = (arr[i] / digit_place) % 10;
			buckets[index][sizes[index]++] = arr[i];
			i++;
		}

		// Merge buckets
		k = 0;
		i = 0;
		while (i < bucket_count)
		{
			j = 0;
			while (j < sizes[i])
			{
				arr[k++] = buckets[i][j];
				j++;
			}
			i++;
		}
		digit_place *= 10; // Move to the next digit position
	}

	// Free memory
	i = 0;
	while (i < bucket_count)
	{
		free(buckets[i]);
		i++;
	}

	free(buckets);
	free(sizes);
}

int	main(void)
{
	int	arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
	int	n = sizeof(arr) / sizeof(arr[0]);
	int	i;

	radix_sort(arr, n);

	i = 0;
	while (i < n)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");

	return (0);
}
