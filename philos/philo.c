/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 23:56:30 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 19:19:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



static void	loop(t_philo *v)
{
	while (1)
	{
		if (ft_stop(v))
			return ;
		while (ft_take_forks(v))
			continue ;
		if (ft_stop(v))
			return ;
		ft_eat(v);
		if (ft_stop(v) || ft_eaten_enough(v))
			return ;
		ft_sleep(v);
		if (ft_stop(v))
			return ;
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

void	*philo(void *args)
{
	t_philo *v;

	v = (t_philo *)args;
	if (v->id % 2)
		usleep(v->rules->time_to_eat * 1000);
	set_timestamp(&v->time);
	if (exceptions(v))
		return (0);
	loop(v);
	return (0);
}
