/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:27 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:54:28 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	lsts_init(t_list **params_receiver,
	t_list **lst1, t_list **lst2, t_list **actions)
{
	(*params_receiver) = NULL;
	(*lst1) = NULL;
	(*lst2) = NULL;
	(*actions) = NULL;
}

void	t_list_free(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	lsts_free(t_list *params, t_list *lst1, t_list *lst2, t_list *actions)
{
	t_list_free(params);
	t_list_free(lst1);
	t_list_free(lst2);
	t_list_free(actions);
}

void	actions_if_forest(int act)
{
	if (act == SA)
		write(1, "sa", 2);
	if (act == SB)
		write(1, "sb", 2);
	if (act == SS)
		write(1, "ss", 2);
	if (act == RA)
		write(1, "ra", 2);
	if (act == RB)
		write(1, "rb", 2);
	if (act == RR)
		write(1, "rr", 2);
	if (act == RRA)
		write(1, "rra", 3);
	if (act == RRB)
		write(1, "rrb", 3);
	if (act == RRR)
		write(1, "rrr", 3);
	if (act == PA)
		write(1, "pb", 2);
	if (act == PB)
		write(1, "pa", 2);
	write(1, "\n", 1);
}

void	actions_print(t_list *actions)
{
	t_list	*tmp;

	if (!(actions))
	{
		write(1, "\n", 1);
		return ;
	}
	tmp = actions;
	while (tmp)
	{
		actions_if_forest(tmp->nb);
		tmp = tmp->next;
	}
}
