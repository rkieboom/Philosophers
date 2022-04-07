/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:54:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 22:42:16 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	waiting_to_start(t_thread *v)
{
	pthread_mutex_lock(&v->mutex);
	v->ready = 1;
	pthread_mutex_unlock(&v->mutex);
	printf("philo %i ready!\n", v->id);
	while (1)
	{
		// printf("%i. in loop\n", v->id);
		// fflush(0);
		pthread_mutex_lock(&v->mutex);
		if (v->start == 1)
		{		
			pthread_mutex_unlock(&v->mutex);
			break ;
		}
		pthread_mutex_unlock(&v->mutex);
		usleep(3000);
	}
	pthread_mutex_lock(&v->mutex);
	v->first_timestamp = get_time();
	v->timestamp_since_eaten = v->first_timestamp;
	pthread_mutex_unlock(&v->mutex);
	if (!(v->id % 2))
		usleep(v->values->time_to_eat * 1000);
}

static int	eaten_enough_times(t_thread *v)
{
	if (v->values->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	else if (v->eat_count == \
	v->values->number_of_times_each_philosopher_must_eat)
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
		pthread_mutex_unlock(&v->forks->fork);
		pthread_mutex_unlock(&v->forks->right->fork);
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

static int	execptions(t_thread *v)
{
	if (v->values->number_of_times_each_philosopher_must_eat == 0)
		return (0);
	else if (v->values->number_of_philosophers == 1)
	{
		while (1)
		{
			if (philo_died(v))
				return (0);
			usleep(1000);
		}
	}
	else
		return (1);
	return (0);
}

void	*philosophers(void *args)
{
	t_thread	*v;

	v = (t_thread *)args;
	waiting_to_start(v);
	if (execptions(v))
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
