/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_pswap01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:51:48 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:51:52 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	pa(t_list **lst1, t_list **lst2, t_list **actions)
{
	t_list	*tmp;

	if (!(*lst1))
		return ;
	tmp = (*lst1);
	(*lst1) = (*lst1)->next;
	tmp->next = NULL;
	ft_lstadd_front(lst2, tmp);
	ft_lstadd_back(actions, ft_lstnew(PA));
}

void	pb(t_list **lst1, t_list **lst2, t_list **actions)
{
	t_list	*tmp;

	if (!(*lst2))
		return ;
	tmp = (*lst2);
	(*lst2) = (*lst2)->next;
	tmp->next = NULL;
	ft_lstadd_front(lst1, tmp);
	ft_lstadd_back(actions, ft_lstnew(PB));
}

void	rr(t_list **lst1, t_list **lst2, t_list **actions)
{
	ra(lst1, actions, 1);
	rb(lst2, actions, 1);
	ft_lstadd_back(actions, ft_lstnew(RR));
}

void	rrr(t_list **lst1, t_list **lst2, t_list **actions)
{
	rra(lst1, actions, 1);
	rrb(lst2, actions, 1);
	ft_lstadd_back(actions, ft_lstnew(RRR));
}
