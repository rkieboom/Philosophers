/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 20:56:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:52:59 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

void	threads_ready(t_thread *v)
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

// int	threads_done(t_thread *v)
// {
// 	int	i;

// 	i = 0;
// 	while (i < v->values->number_of_philosophers)
// 	{
// 		if (v[i].ready == 1)
// 			break ;
// 		i++;
// 	}
// 	if (i == v->values->number_of_philosophers)
// 		return (1);
// 	return (0);
// }

static int	loop(t_thread *v, int i)
{
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{
			if (get_time() - v[i].timestamp_since_eaten > \
			v[i].values->time_to_die && v[i].timestamp_since_eaten != 0 && \
			v[i].eat_count != \
			v[i].values->number_of_times_each_philosopher_must_eat)
			{
				usleep(3000);
				printf("%lims %i died!\n", get_time() \
				- v[i].first_timestamp, i + 1);
				return (0);
			}
			// if (threads_done(v))
			// 	return (0);
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
	threads_ready(v);
	while (i < v->values->number_of_philosophers)
	{
		pthread_mutex_lock(&v[i].mutex);
		v[i].start = 1;
		pthread_mutex_unlock(&v[i].mutex);
		i++;
	}
	sleep(3);
	printf("monitoring thread closing...\n");
	// loop(v, 0);
	return (0);
}
