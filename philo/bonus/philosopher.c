/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:23:41 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:23:43 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	actual_time(void)
{
	long int		time;
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	time = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (time);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = actual_time();
	while ((actual_time() - time) < ms)
		usleep(ms);
}

int	lock(t_philo *philo)
{
	sem_wait(philo->sem);
	if (!(*philo->dead))
		printf("\033[0;32m%02ld:%06d : [%d] start to eat\n\033[0m",
			philo->inter->tv_sec % 100,
			philo->inter->tv_usec, philo->num);
	else
	{
		sem_post(philo->sem);
		return (0);
	}
	gettimeofday(philo->last_eat, NULL);
	return (1);
}

int	unlock(t_philo *philo)
{
	philo->meal_nbr -= 1;
	sem_post(philo->sem);
	if (philo->meal_nbr == 0)
		return (0);
	printf("\033[0;37m%02ld:%06d : [%d] start to sleep\n\033[0m",
		philo->inter->tv_sec % 100,
		philo->inter->tv_usec, philo->num);
	return (1);
}

void	eat_sleep_think_repeat(t_philo *philo)
{
	while (!(*philo->dead))
	{
		if (philo->status == EAT)
		{
			if (!lock(philo))
				return ;
			ft_usleep(philo->delta_max_eat);
			if (!unlock(philo))
				return ;
			philo->status = SLEEP;
		}
		else if (philo->status == SLEEP)
		{
			ft_usleep(philo->delta_max_sleep);
			philo->status = THINK;
		}
		else if (philo->status == THINK)
		{
			printf("\033[0;36m%02ld:%06d : [%d] start to think\n\033[0m",
				philo->inter->tv_sec % 100, philo->inter->tv_usec, philo->num);
			philo->status = EAT;
		}
	}
}
