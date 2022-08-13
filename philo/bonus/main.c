/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:20:30 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:20:33 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	t_args	args;
	sem_t	*sem;

	if (!parsing_entry(argc, argv)
		|| !parsing_value(&args, argc, argv))
		return (1);
	sem_unlink(SEM_NAME);
	sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, (args.num / 2));
	process_init(&args);
	sem_close(sem);
	return (0);
}
