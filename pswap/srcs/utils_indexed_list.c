/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_indexed_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:54:20 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/25 10:36:01 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	lst_min_max_size(t_list **params_receiver, t_pos *pos)
{
	t_list	*tmp;

	tmp = (*params_receiver);
	pos->max = tmp->nb;
	pos->min = tmp->nb;
	while (tmp)
	{
		if (tmp->nb > pos->max)
			pos->max = tmp->nb;
		if (tmp->nb < pos->min)
			pos->min = tmp->nb;
		tmp = tmp->next;
		pos->size++;
	}
}

int	there_are_still_nbrs(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] >= '0' && str[j] <= '9')
			return (1);
		j++;
	}
	return (0);
}

int	affect_with_maxInt_handling(t_list **lst, char **str, int i, int *j)
{
	long int	nb;
	t_list		*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	nb = ft_atoi_custom(&str[i][(*j)], j);
	if (nb > 2147483647 || nb < -2147483648)
	{
		free(tmp);
		t_list_free(*lst);
		w_error();
		return (0);
	}
	else
	{
		tmp->nb = nb;
		tmp->next = NULL;
		ft_lstadd_back(lst, tmp);
		return (1);
	}
}

t_list	*list_from_params(int argc, char **str)
{
	int		i;
	int		j;
	t_list	*lst;

	i = 1;
	j = 0;
	lst = NULL;
	while (i < argc)
	{
		while (str[i][j])
		{
			if (there_are_still_nbrs(&str[i][j]))
			{
				if (!affect_with_maxInt_handling(&lst, str, i, &j))
					return (NULL);
			}
			else
				return (lst);
		}
		j = 0;
		i++;
	}
	return (lst);
}
