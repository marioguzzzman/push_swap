/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maguzman <maguzman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:29:26 by maguzman          #+#    #+#             */
/*   Updated: 2026/07/08 16:36:49 by maguzman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>
#include "libft/libft.h"

// Function to create a new node with given value as data

t_node	*createNode(int data)
{
	t_node	*newNode = malloc(sizeof(t_node));

	newNode->value = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	return (newNode);
}

// Function to insert a node at the beginning

void	insertAtBeginning(t_node **head, int data)
{
	// creating new node
	t_node	*newNode = createNode(data);

	// check if DLL is empty
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	newNode->next = *head;
	(*head)->prev = newNode;
	*head = newNode;
}

// Function to insert a node at the end

void	insertAtEnd(t_node **head, int data)
{
	// creating new node
	t_node	*newNode = createNode(data);

	// check if DLL is empty
	if (*head == NULL)
	{
		*head = newNode;
		return ;
	}
	t_node	*temp = *head;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	newNode->prev = temp;
}

// Function to insert a node at a specified position

void	insertAtPosition(t_node **head, int data, int position)
{
	if (position < 1)
	{
		printf("Position should be >= 1.\n");
		return ;
	}
	// if we are inserting at head
	if (position == 1)
	{
		insertAtBeginning(head, data);
		return ;
	}
	t_node	*newNode = createNode(data);
	t_node	*temp = *head;

	for (int i = 1; temp != NULL && i < position - 1; i++)
	{
		temp = temp->next;
	}
	if (temp == NULL)
	{
		printf(
			"Position greater than the number of nodes.\n");
		return ;
	}
	newNode->next = temp->next;
	newNode->prev = temp;
	if (temp->next != NULL)
	{
		temp->next->prev = newNode;
	}
	temp->next = newNode;
}
