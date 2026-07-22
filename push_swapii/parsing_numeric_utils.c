/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_numeric_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 13:01:53 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/22 17:52:08 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

// has_duplicate: scan over the not-yet-linked value array

int	has_duplicate(long *values, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (values[i] == values[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
build_stack_from_values: allocates one t_stack node per value and links
them so the first value given becomes the TOP of stack a.
*/

int	build_stack_from_values(t_data *data, long *values, int n)
{
	int		i;
	t_stack	*node;

	i = n - 1;
	while (i >= 0)
	{
		node = malloc(sizeof(t_stack));
		if (!node)
			return (0);
		node->value = values[i];
		node->rank = 0;
		node->next = NULL;
		stack_add_top(&data->a, node);
		i--;
	}
	return (1);
}

int	validate(int n, long *values, char **tokens)
{
	int	i;
	int	ok;

	i = 0;
	while (i < n)
	{
		if (!ft_str_is_number(tokens[i]))
			return (1);
		ok = 1;
		values[i] = token_to_long(tokens[i], &ok);
		if (!ok)
			return (1);
		i++;
	}
	return (0);
}
