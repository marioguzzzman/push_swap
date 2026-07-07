/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/03 17:44:15 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/07 14:43:16 by maguzman        ###   ########.fr        */
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

	i = 1;
	j = 0;
	if (argc > 1)
	{
		while (i < argc)
		{
			// write(1, "arg: [", 6);
			// write(1, argv[i], ft_strlen(argv[i]));
			// write(1, "]\n", 2);
			array = ft_split(argv[i], ' ');
			while (array[j] != NULL)
			{
				//assign into double link list
				printf("array %s\n", array[j]);
				j++;
			}
			i++;
		}
	}
	else
		return (1);
	return (0);
}
