/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 16:40:31 by dbali             #+#    #+#             */
/*   Updated: 2026/07/08 14:54:55 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Bucket sort

// 1. create an array (each element = a bucket)
// 2. multiply each element by the array size and get the result
// 3. put each element in the respective bucket based on the result
// 4. use insertion sort to sort each element inside a bucket
// 5. put together each element of the bucket

/*
	Example: 0.23 * 10 = 2.3 == 2 ==> SECOND BUCKET
*/

#include <stdio.h>
#include <stdlib.h>

void	insertion_sort(int arr[], int n);

// int arr[] = array to sort
// int n = number of elements in arr
void	bucket_sort(int arr[], int n)
{
	int	min; // Min value
	int	max; // Max value
	int	i; // Index for arr
	int	bucket_count; // How many buckets are needed
	int	**buckets; // Array of buckets
	int	*sizes; // How many elements are stored in a bucket
	int	index; // The bucket number where an element must be placed
	int	j;
	int	k;

	// Initialize min and max to the first element
	min = arr[0];
	max = arr[0];
	i = 1; // Start at the second element
	while (i < n) // Check each element and update min / max
	{
		if (arr[i] < min)
			min  = arr[i];
		if (arr[i] > max)
			max = arr[i];
		i++;
	}

	bucket_count = n; // We need n buckets
	buckets = malloc(n * sizeof(int *));
	sizes = calloc(bucket_count, sizeof(int)); // Has to start with all values set to 0

	i = 0;
	while (i < n) // Allocate memory for each bucket
	{
		buckets[i] = malloc(n * sizeof(int));
		i++;
	}

	i = 0;
	while (i < n)
	{
		/*
			arr[i] = 5
			min = 0
			bucket_count = 10
			max = 9

			(5-0)*10 / (9-0+1) = 6
		*/
		index = (arr[i] - min) * bucket_count / (max - min + 1); // Calculate bucket number
		
		// buckets[index]  ==>  choose the bucket
		// [sizes[index]]  ==>  choose the next empty position inside that bucket
		// = arr[i]  ==>  store the number
		// sizes[index]++  ==>  increase the bucket's element count
		buckets[index][sizes[index]++] = arr[i]; // Store element in bucket
		i++;
	}

	i = 0;
	while (i < bucket_count) // Sort each bucket with insertion sort
	{
		insertion_sort(buckets[i], sizes[i]);
		i++;
		// printf("buckets: %d\n", buckets[0][0]);
	}

  
	// Merge buckets together
	k = 0;
	i = 0;
	while (i < bucket_count) // Go through buckets
	{
		j = 0;
		while (j < sizes[i]) // Go through elements of each bucket
		{
			arr[k++] = buckets[i][j];
			j++;
		}
		i++;
	}

	i = 0;
	while (i < bucket_count)
	{
		free(buckets[i]);
		i++;
	}

	free(buckets);
	free(sizes);
}

int main() {
    int arr[] = {20, 30, 60, 50, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucket_sort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    return 0;
}
