/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvt_handler01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 21:53:15 by mberengu          #+#    #+#             */
/*   Updated: 2021/08/16 21:53:16 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	mvt_to_first(int first_pos, int lstsize)
{
	int	obj_first;

	obj_first = -1;
	if (first_pos > 0)
	{
		if (first_pos <= lstsize / 2)
			obj_first = first_pos;
		if (first_pos > lstsize / 2)
			obj_first = (first_pos - lstsize) * -1;
	}
	return (obj_first);
}

int	mvt_to_last(int last_pos, int lstsize)
{
	int	obj_last;

	obj_last = -1;
	if (last_pos > 0)
	{
		if (last_pos <= lstsize / 2)
			obj_last = last_pos;
		if (last_pos > lstsize / 2)
			obj_last = (last_pos - lstsize) * -1;
	}
	return (obj_last);
}

int	mvt_handler(int first_pos, int last_pos, int lstsize, int *f1_l0)
{
	int	obj_first;
	int	obj_last;

	*f1_l0 = 1;
	obj_first = mvt_to_first(first_pos, lstsize);
	obj_last = mvt_to_last(last_pos, lstsize);
	if (obj_last < obj_first && obj_last >= 0)
	{
		*f1_l0 = 0;
		return (obj_last);
	}
	if (obj_first < obj_last && obj_first >= 0)
		return (obj_first);
	return (obj_first);
}
