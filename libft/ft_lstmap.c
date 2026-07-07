/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_lstmap.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: maguzman <maguzman@student.42.fr>         #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/05/26 15:16:14 by maguzman         #+#    #+#              */
/*   Updated: 2026/05/26 18:49:32 by maguzman        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*newnode;
	void	*new_content;

	result = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	while (lst)
	{
		new_content = f(lst->content);
		newnode = ft_lstnew(new_content);
		if (newnode == NULL)
		{
			ft_lstclear(&result, del);
			free(new_content);
			return (NULL);
		}
		ft_lstadd_back(&result, newnode);
		lst = lst->next;
	}
	return (result);
}

/*
DESCRIPTION
Iterates through the list ’lst’, applies the
function ’f’ to each node’s content, and creates
a new list resulting of the successive applications
of the function ’f’. The ’del’ function is used to
delete the content of a node if nee
*/
