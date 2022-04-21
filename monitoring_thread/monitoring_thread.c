/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 13:40:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:39:22 by rkieboom      ########   odam.nl         */
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

static int	philos_done_eating(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->rules->number_of_philos)
	{
		pthread_mutex_lock(&ph[i].eat_count_m);
		if (ph[i].eat_count != ph->rules->amount_of_times_to_eat)
		{
			pthread_mutex_unlock(&ph[i].eat_count_m);
			break ;
		}
		pthread_mutex_unlock(&ph[i].eat_count_m);
		i++;
	}
	if (i == ph->rules->number_of_philos)
		return (1);
	return (0);
}

static int	check_philo_dead(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph[i].eat_count_m);
	if (ph[i].eat_count != ph->rules->amount_of_times_to_eat)
	{
		pthread_mutex_unlock(&ph[i].eat_count_m);
		stop_simulation(ph);
		printf("%lims %i has died!\n", \
		get_time() - ph[i].time.first_timestamp, ph[i].id);
		pthread_mutex_unlock(&ph[i].time.mutex);
		return (1);
	}
	pthread_mutex_unlock(&ph[i].eat_count_m);
	return (0);
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
			if (get_time() - ph[i].time.timestamp_since_eaten > \
			ph->rules->time_to_die && ph[i].time.timestamp_since_eaten != 0)
				if (check_philo_dead(ph, i))
					return ;
			pthread_mutex_unlock(&ph[i].time.mutex);
			usleep(1000);
			i++;
		}
		if (philos_done_eating(ph))
			return ;
		usleep(1000);
	}
}

void	*monitoring_thread(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	start_philos(ph);
	loop(ph);
	return (0);
}
