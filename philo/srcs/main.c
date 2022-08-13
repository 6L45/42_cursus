/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:30:04 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/20 09:30:06 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

float	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)
		+ 1e-6 * (end->tv_usec - start->tv_usec));
}

int	parsing_value(t_args *args, int argc, char **argv)
{
	args->num = ft_atoi(argv[1]);
	args->delta_max_die = ft_atoi(argv[2]);
	args->delta_max_eat = ft_atoi(argv[3]);
	args->delta_max_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->meal_nbr = ft_atoi(argv[5]);
	else
		args->meal_nbr = -1;
	if (args->num <= 0 || args->delta_max_die <= 0
		|| args->delta_max_eat <= 0 || args->delta_max_sleep <= 0)
		return (0);
	if (args->num == 1)
	{
		printf("Need at least 2 philosophers\n");
		return (0);
	}
	return (1);
}

int	parsing_entry(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	j = 0;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j])
				&& !(argv[i][j] >= 0 && argv[i][j] <= 32))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	short			dead;
	short			time_stop;
	t_args			args;

	if (!parsing_entry(argc, argv)
		|| !parsing_value(&args, argc, argv))
		return (1);
	dead = 0;
	time_stop = 0;
	args.dead = &dead;
	args.time_stop = &time_stop;
	threads_init(&args);
	return (0);
}
