/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_solver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:35 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:54:36 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	mouvement_lst1(t_list **lst1, t_list **lst2, t_pos *pos,
			t_list **actions)
{
	if (pos->up_a && pos->up_b)
		rr(lst1, lst2, actions);
	else if (pos->down_a && pos->down_b)
		rrr(lst1, lst2, actions);
	else if (pos->up_a)
		ra(lst1, actions, 0);
	else if (pos->down_a)
		rra(lst1, actions, 0);
}

void	swp_handler(t_list **lst1, t_list **lst2, t_pos *pos, t_list **actions)
{
	if (pos->swap_a && pos->swap_b)
		ss(lst1, lst2, actions);
	else if (pos->swap_a)
		sa(lst1, actions, 0);
	else if (pos->swap_b)
		sb(lst2, actions, 0);
	mvt_to_top(lst1, lst2, pos, actions);
}

int	median_is(t_list **lst1, t_pos *pos)
{
	float	res;
	int		div;
	int		size;

	div = 6;
	size = ft_lstsize(*lst1);
	res = size / div;
	if (res != (int)res)
		res = (int)res ;
	return (find_min(lst1, pos) + (int)res);
}
