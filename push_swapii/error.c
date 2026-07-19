/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:08:44 by dbali             #+#    #+#             */
/*   Updated: 2026/07/13 14:08:56 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// exit_error: never returns
void	exit_error(t_data *data)
{
	free_stack(&data->a);
	free_stack(&data->b);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}