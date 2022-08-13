/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:29:33 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/20 09:29:35 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_args
{
	short			*dead;
	short			*fed;
	short			*time_stop;
	int				num;
	int				delta_max_die;
	int				delta_max_eat;
	int				delta_max_sleep;
	int				meal_nbr;
}				t_args;

typedef struct s_philo
{
	short					status;
	short					out;
	int						num;
	float					delta_max_die;
	float					delta_max_eat;
	float					delta_max_sleep;
	int						meal_nbr;
	pthread_mutex_t			*iright;
	pthread_mutex_t			*ileft;
	short volatile			*dead;
	struct timeval			*last_eat;
	struct timeval			*inter;
}				t_philo;

enum	e_status
{
	EAT = 1,
	SLEEP,
	THINK,
	STOP,
	INIT,
	RIGHT,
	LEFT,
	FREE,
	TAKEN
};

/*minilibft.c-------------------------------------------------*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*ft_calloc(size_t nmemb, size_t size);

/*threads.c---------------------------------------------------*/
void	threads_init(t_args *args);

/*utils.c-----------------------------------------------------*/
void	philo_init(t_philo *philo, pthread_mutex_t **mutex, t_args *args);
void	philo_free(t_philo *philo, t_args *args);
float	time_diff(struct timeval *start, struct timeval *end);
void	all_mutex_init(int total, pthread_mutex_t **mutex);
void	all_mutex_destroy(int total, pthread_mutex_t **mutex);

/*philosopher.c-----------------------------------------------*/
void	philosopher(t_philo *philo);

#endif
