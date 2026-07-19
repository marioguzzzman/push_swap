/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:19:05 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 14:19:07 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

/* int	main(void)
{
	t_list	*head;

	head = NULL;

	ft_lstadd_front(&head, ft_lstnew("aaa "));
	ft_lstadd_front(&head, ft_lstnew("bbb "));
	ft_lstadd_front(&head, ft_lstnew("ccc "));

	while (head)
	{
		printf("%s", (char *)head->content);
		head = head->next;
	}
	return (0);
} */
