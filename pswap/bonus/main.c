/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:52:44 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:52:46 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	norminette_mon_amour(t_list *actions)
{
	if (actions)
	{
		mvt_review(&actions);
		actions_print(actions);
	}
}

int	main(int argc, char **argv)
{
	t_list	*params_receiver;
	t_list	*lst1;
	t_list	*lst2;
	t_list	*actions;
	t_pos	position;

	lsts_init(&params_receiver, &lst1, &lst2, &actions);
	t_pos_init(&position);
	if (arg_checker(argc, argv) && argc >= 2)
	{
		params_receiver = list_from_params(argc, argv);
		if (params_receiver && no_duplicate(&params_receiver))
		{
			lst_min_max_size(&params_receiver, &position);
			lst1 = lst_crea_argsize(&params_receiver, &position);
			stack_order(&params_receiver, &lst1, &position);
			solver(&lst1, &lst2, &position, &actions);
			norminette_mon_amour(actions);
			actions_apply_check(&params_receiver, &lst2, &actions);
		}
	}
	lsts_free(params_receiver, lst1, lst2, actions);
	return (0);
}
