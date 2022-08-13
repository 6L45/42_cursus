/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:20:50 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:20:51 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

typedef struct s_args
{
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
	int						time_stop;
	short volatile			*th_res;
	short volatile			*dead;
	struct timeval			*last_eat;
	struct timeval			*inter;
	sem_t					*sem;
}				t_philo;

typedef struct s_wait
{
	int	pid;
	int	*ids;
	int	total;
	int	*th_res;
}				t_wait;

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

# define SEM_NAME "oh_my_semaphore"

/* ************************************************************************** */
/*main.c----------------------------------------------------------------------*/
float	time_diff(struct timeval *start, struct timeval *end);

/*minilibft.c-----------------------------------------------------------------*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*ft_calloc(size_t nmemb, size_t size);

/*process_init.c--------------------------------------------------------------*/
void	process_init(t_args *args);

/*utils.c---------------------------------------------------------------------*/
void	philo_time_free(t_philo *philo);
void	philo_init(t_philo *philo, t_args *args, int nbr);

/*philosopher.c---------------------------------------------------------------*/
void	eat_sleep_think_repeat(t_philo *philo);

/*process_checker.c-----------------------------------------------------------*/
void	process_checker(t_args *args, int *ids);

#endif
