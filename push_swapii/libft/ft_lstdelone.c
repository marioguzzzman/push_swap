/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbali <dbali@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 14:31:17 by dbali             #+#    #+#             */
/*   Updated: 2026/05/11 14:31:18 by dbali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}

/* void	del_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*head;
	char	*str;

	str = ft_strdup("hello world");
	head = ft_lstnew(str);

	printf("before: %s\n", (char *)head->content);

	ft_lstdelone(head, del_content);
	
	printf("after: deleted");
	return (0);
} */
