/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 23:56:30 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:39:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	loop(t_philo *v)
{
	while (1)
	{
		if (ft_stop(v))
			break ;
		if (ft_take_forks(v))
			break ;
		if (ft_stop(v))
			break ;
		ft_eat(v);
		if (ft_stop(v) || ft_eaten_enough(v))
			break ;
		ft_sleep(v);
		if (ft_stop(v))
			break ;
		ft_think(v);
	}
}

static void	set_timestamp(t_time *time)
{
	pthread_mutex_lock(&time->mutex);
	time->first_timestamp = get_time();
	time->timestamp_since_eaten = get_time();
	pthread_mutex_unlock(&time->mutex);
}

static int	exceptions(t_philo *ph)
{
	if (ph->rules->amount_of_times_to_eat == 0)
		return (1);
	if (ph->rules->number_of_philos == 1)
	{
		while (1)
		{
			if (ft_stop(ph))
				break ;
			usleep(1000);
		}
		return (1);
	}
	return (0);
}

void	waiting_to_start(t_philo *ph)
{
	pthread_mutex_lock(&ph->stop_m);
	ph->start = 1;
	pthread_mutex_unlock(&ph->stop_m);
	while (1)
	{
		pthread_mutex_lock(&ph->stop_m);
		if (ph->start == 2)
		{
			pthread_mutex_unlock(&ph->stop_m);
			break ;
		}
		pthread_mutex_unlock(&ph->stop_m);
		usleep(1000);
	}
}

void	*philo(void *args)
{
	t_philo	*v;

	v = (t_philo *)args;
	set_timestamp(&v->time);
	waiting_to_start(v);
	if (exceptions(v))
		return (0);
	set_timestamp(&v->time);
	if (v->id % 2 == 0)
		usleep(v->rules->time_to_eat * 1000);
	loop(v);
	return (0);
}
