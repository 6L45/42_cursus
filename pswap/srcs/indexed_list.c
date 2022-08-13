/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexed_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:52:34 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:52:36 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	new_min(t_list **params_receiver, t_list **lst1, int prev)
{
	static int	nbr = 2;
	t_list		*tmparam;
	t_list		*tmplst1;
	int			i;

	i = 0;
	tmparam = (*params_receiver);
	tmplst1 = (*lst1);
	while (tmparam->nb != prev)
	{
		tmplst1 = tmplst1->next;
		tmparam = tmparam->next;
	}
	tmplst1->nb = nbr;
	nbr++;
}

void	next_min_init(t_list **params_receiver, int nb, int *prev, int *new)
{
	t_list	*checker;

	checker = (*params_receiver);
	*new = nb;
	while (checker)
	{
		if (checker->nb < *new && checker->nb > *prev)
		{
			*new = checker->nb;
			checker = (*params_receiver);
		}
		checker = checker->next;
	}
	*prev = *new;
}

void	stack_order(t_list **params_receiver, t_list **lst1, t_pos *pos)
{
	int		new;
	int		prev;
	t_list	*tmp;

	prev = pos->min;
	tmp = (*params_receiver);
	while (tmp)
	{
		if (tmp->nb > prev)
		{
			next_min_init(params_receiver, tmp->nb, &prev, &new);
			new_min(params_receiver, lst1, prev);
			tmp = (*params_receiver);
		}
		tmp = tmp->next;
	}
}

void	stack_min_max(t_list **params_receiver, t_list **lst1, t_pos *pos)
{
	t_list	*tmplst;
	t_list	*tmpstk;

	tmplst = (*params_receiver);
	tmpstk = (*lst1);
	while (tmplst)
	{
		if (tmplst->nb == pos->min)
			tmpstk->nb = 1;
		if (tmplst->nb == pos->max)
			tmpstk->nb = pos->size;
		tmpstk = tmpstk->next;
		tmplst = tmplst->next;
	}
}

t_list	*lst_crea_argsize(t_list **params_receiver, t_pos *pos)
{
	int		i;
	t_list	*lst1;
	t_list	*tmp;

	i = 0;
	lst1 = NULL;
	while (i < pos->size)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		tmp->nb = 0;
		tmp->next = NULL;
		ft_lstadd_back(&lst1, tmp);
		i++;
	}
	stack_min_max(params_receiver, &lst1, pos);
	return (lst1);
}
