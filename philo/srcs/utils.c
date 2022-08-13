/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:29:14 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/20 09:29:16 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	all_mutex_destroy(int total, pthread_mutex_t **mutex)
{
	int	i;

	i = 0;
	while (i < total)
	{
		pthread_mutex_destroy(&(*mutex)[i]);
		i++;
	}
}

void	all_mutex_init(int total, pthread_mutex_t **mutex)
{
	int	i;

	i = 0;
	while (i < total)
	{
		pthread_mutex_init(&(*mutex)[i], NULL);
		i++;
	}
}

void	philo_free(t_philo *philo, t_args *args)
{
	int		i;

	i = 0;
	while (i < args->num)
	{
		free(philo[i].last_eat);
		free(philo[i].inter);
		i++;
	}
	i = 0;
	free(philo);
}

int	clamp_value(int nbr, t_args *args, int side)
{
	int	index;

	index = 0;
	if (side == LEFT)
	{
		index = nbr - 2;
		if (nbr == 1)
			index = args->num - 1;
	}
	else if (side == RIGHT)
	{
		index = nbr - 1;
		if (nbr == 1)
			index = 0;
		if (nbr == args->num)
			index = args->num - 1;
	}
	return (index);
}

void	philo_init(t_philo *philo, pthread_mutex_t **mutex, t_args *args)
{
	static int	nbr = 1;

	philo->status = INIT;
	philo->num = nbr;
	philo->out = 0;
	philo->delta_max_die = args->delta_max_die;
	philo->delta_max_eat = args->delta_max_eat;
	philo->delta_max_sleep = args->delta_max_sleep;
	philo->meal_nbr = args->meal_nbr;
	philo->iright = &(*mutex)[clamp_value(nbr, args, RIGHT)];
	philo->ileft = &(*mutex)[clamp_value(nbr, args, LEFT)];
	philo->dead = args->dead;
	philo->last_eat = (struct timeval *)ft_calloc(1, sizeof(struct timeval));
	philo->inter = (struct timeval *)ft_calloc(1, sizeof(struct timeval));
	nbr += 1;
}
