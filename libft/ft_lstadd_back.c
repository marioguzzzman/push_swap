/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_lstadd_back.c                                  :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/21 17:33:53 by maguzman         #+#    #+#              */
/*   Updated: 2026/05/27 16:47:32 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

/*
DESCRIPTION
Adds the node ’new’ at the end of the list.

PARAMETERS
lst: The address of a pointer to the first node of
a list.
new: The address of a pointer to the node to be
added.

RETURN VALUES
None

NOTES:
*/
