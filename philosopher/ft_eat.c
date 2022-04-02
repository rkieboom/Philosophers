/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eat.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 15:17:05 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 16:58:48 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_thread *v, long *timestamp_since_eaten)
{
	long	timestamp;

	timestamp = get_time();
	*timestamp_since_eaten = get_time();
	printf("%lims %i is %seating%s\n", \
	get_time() - v->first_timestamp, v->id, KGRN, KWHT);
	while (timestamp - *timestamp_since_eaten < v->values->time_to_eat)
	{
		timestamp = get_time();
		if (philo_died(v))
			break ;
		usleep(1000);
	}
	v->forks->in_use = 0;
	v->forks->right->in_use = 0;
	if (v->id % 2)
	{
		pthread_mutex_unlock(&v->forks->mutex);
		pthread_mutex_unlock(&v->forks->right->mutex);
	}
	else
	{
		pthread_mutex_unlock(&v->forks->right->mutex);
		pthread_mutex_unlock(&v->forks->mutex);
	}
}
