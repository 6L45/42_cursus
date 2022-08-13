/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt_handler02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:23 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:53:24 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	first_under_median(t_list **lst1, t_pos *pos)
{
	t_list	*tmp;

	tmp = (*lst1);
	while (tmp)
	{
		if (tmp->nb <= pos->median)
			return (tmp->nb);
		tmp = tmp->next;
	}
	return (0);
}

int	last_under_median(t_list **lst1, t_pos *pos)
{
	int		last;
	t_list	*tmp;

	tmp = (*lst1);
	last = 0;
	while (tmp)
	{
		if (tmp->nb <= pos->median)
			last = tmp->nb;
		tmp = tmp->next;
	}
	return (last);
}

void	direction_handler(t_pos *pos, int position, int lstsize)
{
	if (position > 0)
	{
		if (position <= lstsize / 2)
		{
			pos->up_a = 0;
			pos->down_a = 1;
			pos->obj_a = position;
		}
		if (position > lstsize / 2)
		{
			pos->up_a = 1;
			pos->down_a = 0;
			pos->obj_a = (position - lstsize) * -1;
		}
	}
}

void	set_mvt_to_the_closest_under_median_nb(t_list **lst1, t_pos *pos)
{
	int	first_pos;
	int	last_pos;
	int	lstsize;
	int	first1_last0;

	pos->up_a = 0;
	pos->down_a = 0;
	pos->obj_a = 0;
	first_pos = vertical_check_pos(lst1, first_under_median(lst1, pos));
	last_pos = vertical_check_pos(lst1, last_under_median(lst1, pos));
	lstsize = ft_lstsize((*lst1));
	pos->obj_a = mvt_handler(first_pos, last_pos, lstsize, &first1_last0);
	if (first1_last0)
		direction_handler(pos, first_pos, lstsize);
	else
		direction_handler(pos, last_pos, lstsize);
}
