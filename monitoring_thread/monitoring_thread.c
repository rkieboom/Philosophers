/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 13:40:26 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/14 04:04:36 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	stop_simulation(t_philo *ph)
{
	int	i;

	i = 0;
	printf("stopping simulation\n");
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
					pthread_mutex_unlock(&ph[i].eat_count_m);
					stop_simulation(ph);
					printf("%lims %i has died!\n", get_time() - ph[i].time.first_timestamp, ph[i].id);
					pthread_mutex_unlock(&ph[i].time.mutex);
					return ;
				}
				pthread_mutex_unlock(&ph[i].eat_count_m);
			}
			pthread_mutex_unlock(&ph[i].time.mutex);
			usleep(1000);
			i++;
		}
		if (philos_done_eating(ph))
			return ;
		usleep(1000);
	}
}

void	start_philos(t_philo *v)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < v->rules->number_of_philos)
		{
			pthread_mutex_lock(&v[i].stop_m);
			if (v[i].start != 1)
			{
				pthread_mutex_unlock(&v[i].stop_m);
				break ;
			}
			pthread_mutex_unlock(&v[i].stop_m);
			i++;
		}
		if (i == v->rules->number_of_philos)
		{
			printf("Everyone can start! :)\n");
			i = 0;
			while (i < v->rules->number_of_philos)
			{
				pthread_mutex_lock(&v[i].stop_m);
				v[i].start = 2;
				pthread_mutex_unlock(&v[i].stop_m);
				i++;
			}
			return ;
		}
	}
}

void	*monitoring_thread(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	printf("monitoring started\n");
	start_philos(ph);
	loop(ph);
	return (0);
}
