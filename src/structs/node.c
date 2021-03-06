/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:59:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/03/30 03:29:21 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_node	*new_node(void)
{
	t_node	*new;

	new = ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->tokens = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_node	*get_last_node(t_node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

t_node	*append_node(t_node **head, t_node *new)
{
	t_node	*last;

	if (!(*head))
		*head = new;
	else
	{
		last = get_last_node(*head);
		last->next = new;
		new->prev = last;
	}
	return (new);
}
