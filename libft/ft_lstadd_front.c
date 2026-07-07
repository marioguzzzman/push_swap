/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 16:35:23 by maguzman          #+#    #+#             */
/*   Updated: 2026/05/21 17:39:46 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
DESCRIPTION
Adds the node ’new’ at the beginning of the list.

PARAMETERS
lst: The address of a pointer to the first node of
a list.
new: The address of a pointer to the node to be
added.

RETURN VALUES
None

NOTES:
new is a node.
The next of new goes to the beginning of the list.
The beginning of the list is now the address of new.
If new is NULL, there's no valid address to go to.
The CPU tries to access memory at address 0,
which is not allowed and will produce crash (segmentation fault).
*/
