/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:35:45 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 12:35:47 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst != NULL && new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* int	main(void)
{
	t_list	*head;
	t_list *new_node;

	head = ft_lstnew("world");
	new_node = ft_lstnew("hello ");

	ft_lstadd_front(&head, new_node);

	while (head)
	{
		printf("%s", (char *)head->content);
		head = head->next;
	}
	return (0);
} */
