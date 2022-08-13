/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pswap_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:33 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:53:34 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	last_mvt(t_list **actions)
{
	t_list	*tmp;

	if (!(*actions))
		return (0);
	tmp = (*actions);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->nb);
}

int	swap_lst2_status(t_list **lst2, t_pos *pos, t_list **actions)
{
	int	lst_mv;

	lst_mv = last_mvt(actions);
	pos->swap_b = 0;
	if ((*lst2) && (*lst2)->next && lst_mv != SB && lst_mv != SS)
	{
		if ((*lst2)->nb + 1 == (*lst2)->next->nb)
			pos->swap_b = 1;
		if ((*lst2)->next->next)
		{
			if ((*lst2)->nb + 1 == (*lst2)->next->next->nb
				|| (*lst2)->nb + 1 == (*lst2)->next->next->nb)
				pos->swap_b = 1;
		}
	}
	return (pos->swap_b);
}

int	swap_lst1_status(t_list **lst1, t_pos *pos, t_list **actions)
{
	int	lst_mv;

	lst_mv = last_mvt(actions);
	pos->swap_a = 0;
	if ((*lst1)->next && lst_mv != SA && lst_mv != SS)
	{
		if ((*lst1)->nb - 1 == (*lst1)->next->nb)
			pos->swap_a = 1;
		if ((*lst1)->next->next)
		{
			if ((*lst1)->nb - 1 == (*lst1)->next->next->nb
				|| (*lst1)->nb + 1 == (*lst1)->next->next->nb)
				pos->swap_a = 1;
		}
	}
	return (pos->swap_a);
}
