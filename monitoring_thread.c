/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 20:56:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 21:38:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <stdio.h>
#include <stdlib.h>

int	threads_ready(t_thread *v)
{
	int	i;

	i = 0;
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{
			if (v[i].ready == 0)
				break ;
			i++;
		}
		if (i == v->values->number_of_philosophers)
			return (1);
		i = 0;
		usleep(1000);
	}
}

int	threads_done(t_thread *v)
{
	int	i;

	i = 0;
	while (i < v->values->number_of_philosophers)
	{
		if (v[i].ready == 1)
			break ;
		i++;
	}
	if (i == v->values->number_of_philosophers)
		return (1);
}

void	*monitoring_thread(void *args)
{
	t_thread	*v;
	int			i;

	i = 0;
	v = (t_thread *)args;
	if (threads_ready(v))
		*(v->start) = 1;
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{	
			if (get_time() - v[i].timestamp_since_eaten > \
			v[i].values->time_to_die && v[i].timestamp_since_eaten != 0 && \
			v[i].eat_count != v[i].values->number_of_times_each_philosopher_must_eat) /////////hierrrrr beziggg
			{
				*(v->start) = 0;
				usleep(3000);
				printf("%lims %i died!\n", get_time() \
				- v[i].first_timestamp, i + 1);
				return (0);
			}
			if (threads_done(v))
				return (0);
			usleep(1000);
			i++;
		}
		i = 0;
	}
}
