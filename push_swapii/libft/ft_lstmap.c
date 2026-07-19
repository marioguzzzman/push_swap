/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:22:18 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 15:22:21 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>
// #include <string.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_lst = NULL;
	new_node = NULL;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

/* void	*dup_content(void *content)
{
	return (strdup((char *)content));
}

void	print_content(void *content)
{
	if (content)
	printf("%s\n", (char *)content);
}

void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *lst = NULL;
	t_list *new_lst = NULL;

	ft_lstadd_front(&lst, ft_lstnew("hello"));
	ft_lstadd_front(&lst, ft_lstnew("world"));

	printf("before:\n");
	ft_lstiter(lst, print_content);

	new_lst = ft_lstmap(lst, dup_content, del_content);

	printf("\nafter:\n");
	ft_lstiter(new_lst, print_content);

	ft_lstclear(&lst, del_content);
	ft_lstclear(&new_lst, del_content);
	return (0);
} */
