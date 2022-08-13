/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:01 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:54:01 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	mvt_to_top(t_list **lst1, t_list **lst2, t_pos *pos, t_list **actions)
{
	set_mvt_to_the_closest_under_median_nb(lst1, pos);
	if (swap_lst1_status(lst1, pos, actions))
	{
		swp_handler(lst1, lst2, pos, actions);
		mvt_to_top(lst1, lst2, pos, actions);
	}
	while (pos->obj_a)
	{
		set_mvt_lst2(lst2, pos);
		mouvement_lst1(lst1, lst2, pos, actions);
		pos->obj_a--;
	}
}

int	there_are_under_median_nb(t_list **lst1, t_pos *pos)
{
	t_list	*tmp;

	tmp = (*lst1);
	while (tmp)
	{
		if (tmp->nb <= pos->median)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	lst1_is_ordered(t_list **lst1, t_pos *pos)
{
	t_list	*tmp;

	tmp = (*lst1);
	if (tmp->next)
	{
		while (tmp)
		{
			if (tmp->next && tmp->nb == pos->size)
				tmp = tmp->next;
			if (tmp->next && tmp->nb + 1 != tmp->next->nb)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

void	solver(t_list **lst1, t_list **lst2, t_pos *pos, t_list **actions)
{
	short	is_ordered;

	is_ordered = lst1_is_ordered(lst1, pos);
	while (!is_ordered)
	{
		pos->median = median_is(lst1, pos);
		while (there_are_under_median_nb(lst1, pos) && !is_ordered)
		{
			// determine which number under median is te closest to bring at the top of the list
			mvt_to_top(lst1, lst2, pos, actions);
			is_ordered = lst1_is_ordered(lst1, pos);
			// if number is equal or under the median AND list ain't ordered pass element to b
			if ((*lst1)->nb <= pos->median && !is_ordered)
				pa(lst1, lst2, actions);
		}
	}
	set_order(lst1, lst2, pos, actions);
}
