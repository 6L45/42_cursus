/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:21:02 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:21:04 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_init(t_philo *philo, t_args *args, int nbr)
{
	philo->last_eat = (struct timeval *)ft_calloc(1,
			sizeof(struct timeval));
	philo->inter = (struct timeval *)ft_calloc(1,
			sizeof(struct timeval));
	philo->num = nbr;
	philo->out = 0;
	philo->meal_nbr = args->meal_nbr;
	philo->time_stop = 0;
	philo->delta_max_die = args->delta_max_die;
	philo->delta_max_eat = args->delta_max_eat;
	philo->delta_max_sleep = args->delta_max_sleep;
}

void	philo_time_free(t_philo *philo)
{
	free((void *)philo->last_eat);
	free((void *)philo->inter);
}
