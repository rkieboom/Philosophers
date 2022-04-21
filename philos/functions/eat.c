/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eat.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:51 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:22:50 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_eat(t_philo *v)
{
	long	timestamp;

	timestamp = get_time();
	pthread_mutex_lock(&v->stop_m);
	if (v->stop == 1)
	{
		pthread_mutex_unlock(&v->stop_m);
		return ;
	}
	printf("%lims %i is %seating%s\n", \
	get_time() - v->time.first_timestamp, v->id, KGRN, KWHT);
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
	pthread_mutex_lock(&v->eat_count_m);
	v->eat_count++;
	pthread_mutex_unlock(&v->eat_count_m);
}
