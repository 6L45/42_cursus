/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:42 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:53:43 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_mvt_lst2(t_list **lst2, t_pos *pos)
{
	int	max;
	int	max_pos;
	int	lstsize;

	pos->up_b = 0;
	pos->down_b = 0;
	pos->obj_b = 0;
	max = (int)find_max(lst2);
	max_pos = vertical_check_pos(lst2, max);
	lstsize = ft_lstsize((*lst2));
	if (max_pos > 0)
	{
		if (max_pos <= lstsize / 2)
		{
			pos->up_b = 0;
			pos->down_b = 1;
			pos->obj_b = max_pos;
		}
		if (max_pos > lstsize / 2)
		{
			pos->up_b = 1;
			pos->down_b = 0;
			pos->obj_b = (max_pos - lstsize) * -1;
		}
	}
}

void	set_mvt_lst1(t_list **lst1, t_pos *pos)
{
	int	min;
	int	min_pos;
	int	lstsize;

	pos->up_a = 0;
	pos->down_a = 0;
	pos->obj_a = 0;
	min = (int)find_min(lst1, pos);
	min_pos = vertical_check_pos(lst1, min);
	lstsize = ft_lstsize((*lst1));
	if (min_pos > 0)
	{
		if (min_pos <= lstsize / 2)
		{
			pos->up_a = 0;
			pos->down_a = 1;
			pos->obj_a = min_pos;
		}
		if (min_pos > lstsize / 2)
		{
			pos->up_a = 1;
			pos->down_a = 0;
			pos->obj_a = (min_pos - lstsize) * -1;
		}
	}
}

void	lst1_order(t_list **lst1, t_list **lst2, t_pos *pos, t_list **actions)
{
	set_mvt_lst1(lst1, pos);
	while (pos->obj_a)
	{
		set_mvt_lst2(lst2, pos);
		if (pos->up_a && pos->up_b)
			rr(lst1, lst2, actions);
		else if (pos->down_a && pos->down_b)
			rrr(lst1, lst2, actions);
		else if (pos->up_a)
			ra(lst1, actions, 0);
		else if (pos->down_a)
			rra(lst1, actions, 0);
		pos->obj_a--;
	}
}

void	mvt_max_top_lst2(t_list **lst2, t_pos *pos, t_list **actions)
{
	set_mvt_lst2(lst2, pos);
	if (swap_lst2_status(lst2, pos, actions))
	{
		sb(lst2, actions, 0);
		mvt_max_top_lst2(lst2, pos, actions);
	}
	while (pos->obj_b)
	{
		if (pos->up_b)
			rb(lst2, actions, 0);
		else if (pos->down_b)
			rrb(lst2, actions, 0);
		pos->obj_b--;
	}
}

void	set_order(t_list **lst1, t_list **lst2, t_pos *pos, t_list **actions)
{
	lst1_order(lst1, lst2, pos, actions);
	while (*lst2)
	{
		mvt_max_top_lst2(lst2, pos, actions);
		pb(lst1, lst2, actions);
	}
}
