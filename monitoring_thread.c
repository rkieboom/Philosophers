/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 20:56:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/08 00:35:56 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

void	threads_start(t_thread *v)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{
			pthread_mutex_lock(&v[i].mutex);
			if (v[i].ready == 0)
			{
				pthread_mutex_unlock(&v[i].mutex);
				break ;
			}
			pthread_mutex_unlock(&v[i].mutex);
			i++;
		}
		usleep(1000);
		if (i == v->values->number_of_philosophers)
			return ;
		i = 0;
	}
}

void	stop_threads(t_thread *v)
{
	int	i;

	i = 0;
	while (i < v->values->number_of_philosophers)
	{
		pthread_mutex_lock(&v[i].mutex);
		v[i].died = 1;
		pthread_mutex_unlock(&v[i].mutex);
		i++;
	}
}

static void	loop(t_thread *v, int i)
{
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{
			pthread_mutex_lock(&v[i].mutex);
			if (get_time() - v[i].timestamp_since_eaten > \
			v[i].values->time_to_die && v[i].timestamp_since_eaten != 0 && \
			v[i].eat_count != \
			v[i].values->number_of_times_each_philosopher_must_eat)
			{
				pthread_mutex_unlock(&v[i].mutex);
				stop_threads(v);
				usleep(3000);
				printf("%lims %i died!\n", get_time() \
				- v[i].first_timestamp, i + 1);
				return ;
			}
			pthread_mutex_unlock(&v[i].mutex);
			usleep(1000);
			i++;
		}
		i = 0;
	}
}

void	*monitoring_thread(void *args)
{
	int			i;
	t_thread	*v;

	v = (t_thread *)args;
	i = 0;
	threads_start(v);
	while (i < v->values->number_of_philosophers)
	{
		pthread_mutex_lock(&v[i].mutex);
		v[i].start = 1;
		pthread_mutex_unlock(&v[i].mutex);
		i++;
	}
	printf("monitoring done!\n");
	fflush(0);
	// loop(v, 0);
	return (0);
}
