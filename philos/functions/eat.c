/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:51 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 18:59:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eat(t_philo *v)
{
	long	timestamp;

	timestamp = get_time();
	pthread_mutex_lock(&v->stop_m);
	if (v->stop == 1)
		return ;
	printf("%lims %i is eating\n", get_time() - v->time.first_timestamp, v->id);
	pthread_mutex_unlock(&v->stop_m);
	pthread_mutex_lock(&v->time.mutex);
	v->time.timestamp_since_eaten = get_time();
	pthread_mutex_unlock(&v->time.mutex);
	while (timestamp - v->time.timestamp_since_eaten < v->rules->time_to_eat)
	{
		timestamp = get_time();
		if (ft_stop(v))
			break ;
		usleep(1000);
	}
	if (v->id % 2 && !v->forks->last)
	{
		pthread_mutex_lock(&v->forks->value_m);
		pthread_mutex_lock(&v->forks->next->value_m);
	}
	else
	{
		pthread_mutex_lock(&v->forks->next->value_m);
		pthread_mutex_lock(&v->forks->value_m);
	}
	v->forks->in_use = 0;
	v->forks->next->in_use = 0;
	pthread_mutex_unlock(&v->forks->value_m);
	pthread_mutex_unlock(&v->forks->next->value_m);
}
