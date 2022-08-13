/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:09 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:54:10 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	t_pos_init(t_pos *pos)
{
	pos->swap_a = 0;
	pos->swap_b = 0;
	pos->up_a = 0;
	pos->up_b = 0;
	pos->down_a = 0;
	pos->down_b = 0;
	pos->a_to_b = 0;
	pos->b_to_a = 0;
	pos->obj_a = 0;
	pos->obj_b = 0;
	pos->max = 0;
	pos->min = 0;
	pos->last_a = 0;
	pos->last_b = 0;
	pos->size = 0;
	pos->median = 0;
}

float	find_min(t_list **lst1, t_pos *pos)
{
	int		min;
	t_list	*tmp;

	min = pos->size;
	tmp = (*lst1);
	while (tmp)
	{
		if (tmp->nb < min)
			min = tmp->nb;
		tmp = tmp->next;
	}
	return (min);
}

float	find_max(t_list **lst1)
{
	int		max;
	t_list	*tmp;

	max = 1;
	tmp = (*lst1);
	while (tmp)
	{
		if (tmp->nb > max)
			max = tmp->nb;
		tmp = tmp->next;
	}
	return (max);
}

int	int_pos(t_list **lst1)
{
	int		i;
	t_list	*tmp;

	tmp = (*lst1);
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	vertical_check_pos(t_list **lst1, int nb)
{
	short	position;
	t_list	*tmp;

	position = 0;
	tmp = (*lst1);
	while (tmp)
	{
		if (tmp->nb == nb)
			position = int_pos(&(tmp));
		tmp = tmp->next;
	}
	return (position);
}
