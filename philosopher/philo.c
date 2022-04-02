/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:54:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 21:31:26 by rkieboom      ########   odam.nl         */
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

static int	eaten_enough_times(t_thread *v)
{
	if (v->values->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	else if (v->eat_count == v->values->number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}

static int	loop(t_thread *v)
{
	if (philo_died(v))
		return (1);
	ft_take_forks(v);
	if (philo_died(v))
	{
		pthread_mutex_unlock(&v->forks->mutex);
		pthread_mutex_unlock(&v->forks->right->mutex);
		return (1);
	}
	ft_eat(v, &v->timestamp_since_eaten);
	if (philo_died(v) || eaten_enough_times(v))
		return (1);
	ft_sleep(v);
	if (philo_died(v))
		return (1);
	ft_think(v);
	if (philo_died(v))
		return (1);
	return (0);
}

void	*philosophers(void *args)
{
	t_thread	*v;

	v = (t_thread *)args;
	waiting_to_start(v);
	if (v->values->number_of_philosophers == 1)
	{
		while (1)
		{
			if (philo_died(v))
				break ;
			usleep(1000);
		}
	}
	else
	{
		while (1)
		{
			v->eat_count++;
			if (loop(v))
				break ;
		}
	}

	return (0);
}
