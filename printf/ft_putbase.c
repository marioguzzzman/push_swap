/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 16:57:16 by maguzman          #+#    #+#             */
/*   Updated: 2026/06/20 18:10:14 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putbase(unsigned long n, unsigned int base, char *map)
{
	int	count;

	count = 0;
	if (n >= base)
		count += ft_putbase(n / base, base, map);
	count += write(1, &map[n % base], 1);
	return (count);
}
