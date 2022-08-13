/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:29:25 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/20 09:29:26 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*redirect(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	gettimeofday(philo->inter, NULL);
	if (philo->num % 2 == 0)
	{
		gettimeofday(philo->last_eat, NULL);
		philo->status = EAT;
	}
	else
	{
		usleep(1000);
		gettimeofday(philo->last_eat, NULL);
		philo->status = THINK;
	}
	philosopher(philo);
	philo->out = 1;
	return (NULL);
}

void	*red_thread(void *ptr)
{
	int				rip;
	t_philo			*philo;
	float			delta_max_death;

	rip = 0;
	philo = (t_philo *)ptr;
	delta_max_death = (philo->delta_max_die / 1000);
	gettimeofday(philo->inter, NULL);
	gettimeofday(philo->last_eat, NULL);
	while (!philo->out)
	{
		gettimeofday(philo->inter, NULL);
		if ((time_diff(philo->last_eat, (struct timeval *)philo->inter)
				>= delta_max_death) && !rip)
		{
			*(philo->dead) = 1;
			printf("\033[0;31m%02ld:%06d : [%d] died\n\033[0m",
				philo->inter->tv_sec % 100, philo->inter->tv_usec, philo->num);
			rip = 1;
		}
		usleep(2000);
	}
	return (NULL);
}

void	join_threads(pthread_t **th, pthread_t **th2, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->num)
	{
		pthread_join((*th)[i], NULL);
		pthread_join((*th2)[i], NULL);
		i++;
	}
}

void	threads_init(t_args *args)
{
	int				i;
	pthread_t		*th;
	pthread_t		*th2;
	t_philo			*philo;
	pthread_mutex_t	*mutex;

	i = 0;
	th = (pthread_t *)ft_calloc(args->num, sizeof(pthread_t));
	th2 = (pthread_t *)ft_calloc(args->num, sizeof(pthread_t));
	mutex = (pthread_mutex_t *)ft_calloc(args->num, sizeof(pthread_mutex_t));
	philo = (t_philo *)ft_calloc(args->num, sizeof(t_philo));
	all_mutex_init(args->num, &mutex);
	while (i < args->num)
	{
		philo_init(&philo[i], &mutex, args);
		pthread_create(th + i, NULL, &redirect, &philo[i]);
		pthread_create(th2 + i, NULL, &red_thread, &philo[i]);
		i++;
	}
	join_threads(&th, &th2, args);
	free(th);
	free(th2);
	all_mutex_destroy(args->num, &mutex);
	free(mutex);
	philo_free(philo, args);
}
