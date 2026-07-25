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

// int arr[] = the array of integers
// int n = the number of elements in arr
void	insertion_sort(int arr[], int n)
{
	int	to_sort; // The current element to sort
	int	i; // Index of element currently being sorted
	int	j; // Prev elements

	i = 1; // Second element
	while (i < n)
	{
		to_sort = arr[i]; // to_sort is the current number
		j = i - 1;
		while (j >= 0 && arr[j] > to_sort) // If the prev element is biggerthan the first element
		{
			arr[j + 1] = arr[j]; // Move the bigger element
			j = j - 1; // Move j back again
		}
		arr[j + 1] = to_sort; // Insert the element where it should be
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
