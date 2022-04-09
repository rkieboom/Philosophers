/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 13:40:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 19:17:24 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	stop_simulation(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->rules->number_of_philos)
	{
		pthread_mutex_lock(&ph[i].stop_m);
		ph[i].stop = 1;
		pthread_mutex_unlock(&ph[i].stop_m);
		i++;
	}
}

static void	loop(t_philo *ph)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ph->rules->number_of_philos)
		{
			pthread_mutex_lock(&ph[i].time.mutex);
			if (get_time() - ph[i].time.timestamp_since_eaten > ph->rules->time_to_die \
			&& ph[i].time.timestamp_since_eaten != 0)
			{
				pthread_mutex_lock(&ph[i].eat_count_m);
				if (ph[i].eat_count != ph->rules->amount_of_times_to_eat)
				{
					pthread_mutex_unlock(&ph[i].time.mutex);
					stop_simulation(ph);
					pthread_mutex_unlock(&ph[i].eat_count_m);
					printf("%lims %i has died!\n", get_time() - ph[i].time.first_timestamp, ph[i].id);
					return ;
				}
				pthread_mutex_unlock(&ph[i].eat_count_m);
			}
			pthread_mutex_unlock(&ph[i].time.mutex);
			i++;
		}
	}
}

void	*monitoring_thread(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	loop(ph);
	return (0);
}
