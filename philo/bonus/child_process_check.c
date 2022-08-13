/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberengu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 10:20:23 by mberengu          #+#    #+#             */
/*   Updated: 2021/10/18 10:20:25 by mberengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
/*
void	kill_em_all(t_wait *waiting)
{
	int	i;

	i = 0;
	while (i < waiting->total)
	{
		

}
*/
void	*children_waiting(void *ptr)
{
	t_wait	*waiting;
	int		status;

	waiting = (t_wait *)ptr;
	waitpid(waiting->pid, &status, 0);
	if ((WEXITSTATUS(status)))
		kill(0, SIGQUIT);
	return (NULL);
}

void	process_checker(t_args *args, int *ids)
{
	int			i;
	int			th_res;
	t_wait		*waiting;
	pthread_t	*th;

	i = 0;
	th_res = 0;
	waiting = (t_wait *)ft_calloc(args->num, sizeof(t_wait));
	th = (pthread_t *)ft_calloc(args->num, sizeof(pthread_t));
	while (i < args->num)
	{
		waiting[i].ids = ids;
		waiting[i].total = args->num;
		waiting[i].pid = ids[i];
		waiting[i].th_res = &th_res;
		pthread_create(th + i, NULL, &children_waiting, &waiting[i]);
		i++;
	}
	i = -1;
	while (++i < args->num)
		pthread_join(th[i], NULL);
	free(waiting);
	free(th);
	return ;
}
