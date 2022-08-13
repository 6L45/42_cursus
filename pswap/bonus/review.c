/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   review.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:52 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:53:53 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	cut_to_rr(t_list **actions)
{
	t_list	*tmp;

	(*actions)->nb = RR;
	tmp = (*actions)->next;
	if (tmp->next)
		(*actions)->next = tmp->next;
	else
		(*actions)->next = NULL;
	tmp->next = NULL;
	free(tmp);
}

void	cut_to_rrr(t_list **actions)
{
	t_list	*tmp;

	(*actions)->nb = RRR;
	tmp = (*actions)->next;
	if (tmp->next)
		(*actions)->next = tmp->next;
	else
		(*actions)->next = NULL;
	tmp->next = NULL;
	free(tmp);
}

void	cut_to_ss(t_list **actions)
{
	t_list	*tmp;

	(*actions)->nb = SS;
	tmp = (*actions)->next;
	if (tmp->next)
		(*actions)->next = tmp->next;
	else
		(*actions)->next = NULL;
	tmp->next = NULL;
	free(tmp);
}

void	cut_mvt(t_list **actions)
{
	if ((*actions)->nb == RA || (*actions)->nb == RB)
		cut_to_rr(actions);
	else if ((*actions)->nb == RRA || (*actions)->nb == RRB)
		cut_to_rrr(actions);
	else if ((*actions)->nb == SA || (*actions)->nb == SB)
		cut_to_ss(actions);
}

void	mvt_review(t_list **actions)
{
	t_list	*tmp;
	t_list	*tmp_plus;

	tmp = (*actions);
	tmp_plus = NULL;
	while (tmp->next)
	{
		if ((tmp->nb == RA && tmp->next->nb == RB)
			|| (tmp->nb == RB && tmp->next->nb == RA)
			|| (tmp->nb == RRA && tmp->next->nb == RRB)
			|| (tmp->nb == RRB && tmp->next->nb == RRA)
			|| (tmp->nb == SA && tmp->next->nb == SB)
			|| (tmp->nb == SB && tmp->next->nb == SA))
		{
			cut_mvt(&tmp);
		}
		tmp = tmp->next;
	}
}
