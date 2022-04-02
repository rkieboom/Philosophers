/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:54:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 17:45:03 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	waiting_to_start(t_thread *v)
{
	v->ready = 1;
	while (*(v->start) == 0)
		;
	if (!(v->id % 2))
		usleep(v->values->time_to_eat * 1000);
	v->first_timestamp = get_time();
	v->timestamp_since_eaten = v->first_timestamp;
}

static void	loop(t_thread *v)
{
	while (1)
	{
		if (philo_died(v))
			break ;
		ft_take_forks(v);
		if (philo_died(v))
		{
			pthread_mutex_unlock(&v->forks->mutex);
			pthread_mutex_unlock(&v->forks->right->mutex);
			break ;
		}
		ft_eat(v, &v->timestamp_since_eaten);
		if (philo_died(v))
			break ;
		ft_sleep(v);
		if (philo_died(v))
			break ;
		ft_think(v);
		if (philo_died(v))
			break ;
	}
}

void	*philosophers(void *args)
{
	t_thread	*v;

	v = (t_thread *)args;
	waiting_to_start(v);
	loop(v);
	return (0);
}
