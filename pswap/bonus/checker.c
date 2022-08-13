/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:49:27 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:49:28 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ordem_e_progresso(t_list **lst)
{
	t_list	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (tmp->next && tmp->nb > tmp->next->nb)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	move_it(t_list **params_receiver, t_list **lst2, int act, t_list **tmp)
{
	if (act == SA)
		sa(params_receiver, tmp, 1);
	if (act == SB)
		sb(lst2, tmp, 1);
	if (act == SS)
		ss(params_receiver, lst2, tmp);
	if (act == RA)
		ra(params_receiver, tmp, 1);
	if (act == RB)
		rb(lst2, tmp, 1);
	if (act == RR)
		rr(params_receiver, lst2, tmp);
	if (act == RRA)
		rra(params_receiver, tmp, 1);
	if (act == RRB)
		rrb(lst2, tmp, 1);
	if (act == RRR)
		rrr(params_receiver, lst2, tmp);
	if (act == PA)
		pa(params_receiver, lst2, tmp);
	if (act == PB)
		pb(params_receiver, lst2, tmp);
}

void	i_like_to_move_it(t_list **params_receiver, t_list **lst2, int act)
{
	t_list	*tmp;

	tmp = NULL;
	move_it(params_receiver, lst2, act, &tmp);
	free(tmp);
}

void	actions_apply_check(t_list **params, t_list **lst2, t_list **actions)
{
	t_list	*tmp;

	tmp = (*actions);
	while (tmp)
	{
		i_like_to_move_it(params, lst2, tmp->nb);
		tmp = tmp->next;
	}
	if (ordem_e_progresso(params))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}
