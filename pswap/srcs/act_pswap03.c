/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_pswap03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:52:13 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:52:15 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_list **lst1, t_list **actions, short ss)
{
	t_list	*tmp;
	t_list	*swap;

	if (!(*lst1) || !(*lst1)->next)
		return ;
	swap = (*lst1);
	(*lst1) = (*lst1)->next;
	tmp = (*lst1)->next;
	swap->next = tmp;
	(*lst1)->next = swap;
	if (!ss)
		ft_lstadd_back(actions, ft_lstnew(SA));
}

void	sb(t_list **lst2, t_list **actions, short ss)
{
	t_list	*tmp;
	t_list	*swap;

	if (!(*lst2) || !(*lst2)->next)
		return ;
	swap = (*lst2);
	(*lst2) = (*lst2)->next;
	tmp = (*lst2)->next;
	swap->next = tmp;
	(*lst2)->next = swap;
	if (!ss)
		ft_lstadd_back(actions, ft_lstnew(SB));
}

void	ss(t_list **lst1, t_list **lst2, t_list **actions)
{
	sa(lst1, actions, 1);
	sb(lst2, actions, 1);
	ft_lstadd_back(actions, ft_lstnew(SS));
}
