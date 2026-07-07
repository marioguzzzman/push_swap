/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse_utils.c                                     :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/07 16:56:50 by maguzman         #+#    #+#              */
/*   Updated: 2026/07/07 18:36:10 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include "libft/libft.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	converted;

	i = 0;
	converted = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (converted > (LONG_MAX - (str[i] - '0')) / 10)
			return (NULL);
		// too big, bail before the multiply overflows
		converted = converted * 10 + (str[i] - '0');
		i++;
	}
	return (converted * sign);
}

int	get_numbers(char *argv)
{
	char	**array;
	int		i;

	array = ft_split(argv[i], ' ');
	return (array);
}
