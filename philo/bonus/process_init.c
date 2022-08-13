/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:20:57 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:20:58 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

float	time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec)
		+ 1e-6 * (end->tv_usec - start->tv_usec));
}

void	*red_thread(void *ptr)
{
	int		rip;
	t_philo	*philo;

	rip = 0;
	philo = (t_philo *)ptr;
	gettimeofday(philo->inter, NULL);
	gettimeofday(philo->last_eat, NULL);
	while (!philo->out)
	{
		gettimeofday(philo->inter, NULL);
		if (time_diff(philo->last_eat,
				philo->inter) >= philo->delta_max_die / 1000 && !rip)
		{
			printf("\033[0;31m%02ld:%06d : [%d] died\n\033[0m",
				philo->inter->tv_sec % 100, philo->inter->tv_usec, philo->num);
			*philo->dead = 1;
			*philo->th_res = 1;
			rip = 1;
		}
		usleep(2000);
	}
	return (NULL);
}

void	*redirect(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	gettimeofday(philo->inter, NULL);
	gettimeofday(philo->last_eat, NULL);
	eat_sleep_think_repeat(philo);
	philo->out = 1;
	return (NULL);
}

int	philosopher(t_philo *philo, int num)
{
	short		dead;
	short		th_res;
	pthread_t	th[2];

	dead = 0;
	th_res = 0;
	philo->status = EAT;
	philo->num = num;
	philo->dead = &dead;
	philo->th_res = &th_res;
	philo->sem = sem_open(SEM_NAME, 0);
	pthread_create(th, NULL, &redirect, philo);
	pthread_create(th + 1, NULL, &red_thread, philo);
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	philo_time_free(philo);
	if (*philo->th_res)
		return (0);
	return (1);
}

void	process_init(t_args *args)
{
	int			i;
	int			pid;
	int			*ids;
	t_philo		philo;

	i = -1;
	philo_init(&philo, args, 0);
	ids = (int *)ft_calloc(args->num, sizeof(int));
	while (++i < args->num)
	{
		pid = fork();
		if (pid != 0)
			ids[i] = pid;
		else
		{
			if (!philosopher(&philo, i + 1))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
	}
	if (pid != 0)
		process_checker(args, ids);
	philo_time_free(&philo);
	free(ids);
	return ;
}
