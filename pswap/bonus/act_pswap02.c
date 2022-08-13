/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_pswap02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:52:01 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:52:02 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ra(t_list **lst1, t_list **actions, short rr)
{
	t_list	*tmp;

	if (!(*lst1) || !(*lst1)->next)
		return ;
	tmp = (*lst1);
	(*lst1) = (*lst1)->next;
	tmp->next = NULL;
	ft_lstadd_back(lst1, tmp);
	if (!rr)
		ft_lstadd_back(actions, ft_lstnew(RA));
}

void	rb(t_list **lst2, t_list **actions, short rr)
{
	t_list	*tmp;

	if (!(*lst2) || !(*lst2)->next)
		return ;
	tmp = (*lst2);
	(*lst2) = (*lst2)->next;
	tmp->next = NULL;
	ft_lstadd_back(lst2, tmp);
	if (!rr)
		ft_lstadd_back(actions, ft_lstnew(RB));
}

void	rra(t_list **lst1, t_list **actions, short rrr)
{
	t_list	*swap;
	t_list	*tmp;

	if (!(*lst1) || !(*lst1)->next)
		return ;
	tmp = (*lst1);
	while (tmp->next->next)
		tmp = tmp->next;
	swap = tmp->next;
	tmp->next = NULL;
	ft_lstadd_front(lst1, swap);
	if (!rrr)
		ft_lstadd_back(actions, ft_lstnew(RRA));
}

void	rrb(t_list **lst2, t_list **actions, short rrr)
{
	t_list	*swap;
	t_list	*tmp;

	if (!(*lst2) || !(*lst2)->next)
		return ;
	tmp = (*lst2);
	while (tmp->next->next)
		tmp = tmp->next;
	swap = tmp->next;
	tmp->next = NULL;
	ft_lstadd_front(lst2, swap);
	if (!rrr)
		ft_lstadd_back(actions, ft_lstnew(RRB));
}
