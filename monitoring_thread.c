/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring_thread.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/01 20:56:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 13:29:35 by rkieboom      ########   odam.nl         */
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

void *monitoring_thread(void *args)
{
	t_thread *v = (t_thread*)args;
	int		i;

	i = 0;
	if (threads_ready(v))
	{
		printf("----------\nMonitoring thread started\n----------\n\n");
		*(v->start) = 1;
	}
	while (1)
	{
		while (i < v->values->number_of_philosophers)
		{
			// printf("%i. get_time=%li timestamp_since_eaten=%li   --- -= %li\n\n", i, get_time(), time[i]->timestamp_since_eaten, get_time() - time[i]->timestamp_since_eaten);
			
			if (get_time() - v[i].timestamp_since_eaten > v[i].values->time_to_die && v[i].timestamp_since_eaten != 0)
			{
				printf("%i. died!\n%lims", i+1, get_time() - v[i].timestamp_since_eaten);
				exit(1);
			}
			usleep(1000);
			i++;
		}
		i = 0;
	}
}