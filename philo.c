/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:54:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/31 20:33:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <sys/time.h>//gettimeofday
#include <stdio.h>//printf
#include <stdlib.h>//exit

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

long	get_time(void)
{
	struct timeval	tp;
	long			milliseconds;

	gettimeofday(&tp, NULL);
	milliseconds = tp.tv_sec * 1000;
	milliseconds += tp.tv_usec / 1000;
	return (milliseconds);
}

void	ft_try_taking_forks(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	while (1)
	{
		if (v->forks->in_use == 0 && v->forks->right->in_use == 0)
		{
			pthread_mutex_lock(&v->forks->mutex);
			pthread_mutex_lock(&v->forks->right->mutex);
			// printf("%i. time_to_die = %li & time_since_eaten = %li\n", v->id, v->values->time_to_die, get_time() - timestamp_since_eaten);
			v->forks->in_use = 1;
			v->forks->right->in_use = 1;
			break ;
		}
		usleep(500);
	}
	printf("%lims/%lims %i has taken %sfork%s\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT);
}

void	ft_eat(t_thread *v, long first_timestamp, long *timestamp_since_eaten)
{
	long	timestamp;

	timestamp = get_time();
	*timestamp_since_eaten = get_time();
	printf("%lims/%lims %i is %seating%s\n", get_time() - first_timestamp, get_time() - *timestamp_since_eaten, v->id, KGRN, KWHT);
	while (timestamp - *timestamp_since_eaten < v->values->time_to_eat)
	{
		// printf("TEST = [%li]\n", timestamp - *timestamp_since_eaten);
		timestamp = get_time();
		usleep(1000);
	}
	// usleep(v->values->time_to_eat * 1000);
	v->hungry = 0;
	v->forks->in_use = 0;
	v->forks->right->in_use = 0;
	pthread_mutex_unlock(&v->forks->mutex);
	pthread_mutex_unlock(&v->forks->right->mutex);
}

void	ft_sleep(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	int timestamp[2];

	timestamp[0] = get_time();
	timestamp[1] = get_time();
	printf("%lims/%lims %i is %ssleeping%s\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KRED, KWHT);
	while (timestamp[0] - timestamp[1] < v->values->time_to_eat)
	{
		// printf("TEST = [%li]\n", timestamp - *timestamp_since_eaten);
		timestamp[0] = get_time();
		usleep(1000);
	}
}

void	ft_think(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	printf("%lims/%lims %i is thinking\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id);
}

int		check_if_alive(long timestamp_since_eaten, t_thread *v)
{
	if (get_time() - timestamp_since_eaten <= v->values->time_to_die)
		return (1);
	printf("%i died! - %lims\n", v->id, get_time()-timestamp_since_eaten);
	fflush(0);
	exit(1);
	return (0);
}


void	*philosophers(void *args)
{
	t_thread	*v;

	v = (t_thread*)args;
	v->first_timestamp = get_time();
	v->timestamp_since_eaten = v->first_timestamp;
	printf("%i. started!\n", v->id);
	while (1)
	{
		if (!check_if_alive(v->timestamp_since_eaten, v))
			break ;
		ft_try_taking_forks(v, v->first_timestamp, v->timestamp_since_eaten);
		if (!check_if_alive(v->timestamp_since_eaten, v))
			break ;
		ft_eat(v, v->first_timestamp, &v->timestamp_since_eaten);
		if (!check_if_alive(v->timestamp_since_eaten, v))
			break ;
		ft_sleep(v, v->first_timestamp, v->timestamp_since_eaten);
		if (!check_if_alive(v->timestamp_since_eaten, v))
			break ;
		ft_think(v, v->first_timestamp, v->timestamp_since_eaten);
		if (!check_if_alive(v->timestamp_since_eaten, v))
			break ;
	}
	return (0);
}