/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre_lepercq <pierre_lepercq@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 14:29:46 by plepercq          #+#    #+#             */
/*   Updated: 2026/09/09 02:10:34 by pierre_lepe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  *ft_lstpop(t_list **lst, t_list *node)
{
    t_list  *tmp;

    if (!lst || !*lst || !node)
        return (NULL);
    if (*lst == node)
    {
        *lst = node->next;
        node->next = NULL;
        return (node);
    }
    tmp = *lst;
    while (tmp->next && tmp->next != node)
        tmp = tmp->next;
    if (tmp->next != node)
        return (NULL);
    tmp->next = node->next;
    node->next = NULL;
    return (node);
}
