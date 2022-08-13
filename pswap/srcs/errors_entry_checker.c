/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_entry_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:52:25 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/17 20:24:04 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	w_error(void)
{
	write(2, "Error\n", 6);
}

int	arg_checker(int argc, char **str)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		while (str[i][j])
		{
			if (!(ft_isdigit((int)str[i][j])
				|| (str[i][j] == '-' && str[i][j + 1] != '-' && str[i][j + 1])
				|| (str[i][j] >= 9 && str[i][j] <= 13) || str[i][j] == 32))
			{
				w_error();
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	no_duplicate(t_list **lst)
{
	t_list	*tmp;
	t_list	*checker;

	tmp = (*lst);
	while (tmp)
	{
		checker = (*lst);
		while (checker)
		{
			if (checker->nb == tmp->nb && checker != tmp)
			{
				w_error();
				return (0);
			}
			checker = checker->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
