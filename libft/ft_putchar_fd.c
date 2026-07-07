/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 17:57:06 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/20 18:22:15 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
DESCRIPTION
outputs a char to a specified file deescriptor.

RETURN VALUES
None

NOTE
0 = standard input (keyboard)
1 = standard output (terminal)
2 = standard error (terminal, but for errors)

Why is substituing write useful?
- some predictability, and naming abstraction conventions.
*/
