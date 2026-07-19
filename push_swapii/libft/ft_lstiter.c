/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:54:12 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 14:54:13 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

/* void	test_func_print_content(void *content)
{
	printf("%s\n", (char *)content);
}

int	main(void)
{
	t_list	*head;
	
	head = NULL;

	ft_lstadd_front(&head, ft_lstnew("aaa"));
	ft_lstadd_front(&head, ft_lstnew("bbb"));
	ft_lstadd_front(&head, ft_lstnew("ccc"));
	ft_lstadd_front(&head, ft_lstnew("ddd"));
	ft_lstadd_front(&head, ft_lstnew("eee"));

	ft_lstiter(head, test_func_print_content);
	return (0);
} */
