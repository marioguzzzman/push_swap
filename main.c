/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 17:44:15 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/08 16:26:08 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	char	**array;
	int		*numbers_len;

	//t_stack	*a;
	i = 1;
	j = 0;
	count = 0;
	if (argc > 1)
	{
		/*init stack a*/
		/*init stack b*/
		while (i < argc)
		{
			array = get_numbers(argv[i], &numbers_len);
			while (array[j] != NULL)
			{
				//a = array[j];
				// assign to singly-link list
				printf("array %s\n", array[j]);
				j++;
			}
			i++;
		}
	}
	else
		return (1);
	//push_swap(a);
	return (0);
}
