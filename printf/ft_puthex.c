/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:02:43 by maguzman          #+#    #+#             */
/*   Updated: 2026/06/21 14:04:20 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int n, char x)
{
	unsigned long	base;
	char			*map;

	base = 16;
	if (x == 'x')
		map = "0123456789abcdef";
	else
		map = "0123456789ABCDEF";
	return (ft_putbase(n, base, map));
}
