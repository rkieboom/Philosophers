/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 14:54:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 15:02:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


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



void	ft_try_taking_forks(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	while (1)
	{
		if (((v->values->time_to_die - v->values->time_to_sleep) / 2) < v->timestamp_since_eaten)
		{
			// printf("%i. is hungry!\n", v->id);
			v->hungry = 1;
		}
		if ((v->forks->in_use == 0 && v->forks->right->in_use == 0) || v->hungry == 1)
		{
			if (v->values->number_of_philosophers % 2)
				if (v->id % 2 && v->hungry == 0)
					usleep(500);
			if (v->hungry == 1)
			{
				if (v->forks->in_use && !v->forks->right->in_use)
				{
						pthread_mutex_lock(&v->forks->right->mutex);
						printf("%lims/%lims %i has taken %sright fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id + 1);
						pthread_mutex_lock(&v->forks->mutex);
						printf("%lims/%lims %i has taken %sleft fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id);
				}
				else if (!v->forks->in_use && v->forks->right->in_use)
				{
						pthread_mutex_lock(&v->forks->right->mutex);
				printf("%lims/%lims %i has taken %sright fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id + 1);
				pthread_mutex_lock(&v->forks->mutex);
				printf("%lims/%lims %i has taken %sleft fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id);
				}
				else if (v->forks->in_use && v->forks->right->in_use)
					continue;
				else
				{
					pthread_mutex_lock(&v->forks->right->mutex);
						printf("%lims/%lims %i has taken %sright fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id + 1);
						pthread_mutex_lock(&v->forks->mutex);
						printf("%lims/%lims %i has taken %sleft fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id);
				}
					
			}
			else if (v->id % 2)//on even
			{
				pthread_mutex_lock(&v->forks->mutex);
				printf("%lims/%lims %i has taken %sleft fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id);
				pthread_mutex_lock(&v->forks->right->mutex);
				printf("%lims/%lims %i has taken %sright fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id + 1);
			}
			else//even
			{
				pthread_mutex_lock(&v->forks->right->mutex);
				printf("%lims/%lims %i has taken %sright fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id + 1);
				pthread_mutex_lock(&v->forks->mutex);
				printf("%lims/%lims %i has taken %sleft fork%s - %i\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KBLU, KWHT, v->id);
			}
			v->forks->in_use = 1;
			v->forks->right->in_use = 1;
			v->hungry = 0;
			break ;
			
		}
	}
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
	v->forks->in_use = 0;
	v->forks->right->in_use = 0;
	if (v->id % 2)
	{
		pthread_mutex_unlock(&v->forks->mutex);
		pthread_mutex_unlock(&v->forks->right->mutex);
	}
	else
	{
		pthread_mutex_unlock(&v->forks->right->mutex);
		pthread_mutex_unlock(&v->forks->mutex);
	}
}

void	ft_sleep(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	int timestamp[2];

	timestamp[0] = get_time();
	timestamp[1] = get_time();
	printf("%lims/%lims %i is %ssleeping%s\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id, KRED, KWHT);
	while (timestamp[0] - timestamp[1] < v->values->time_to_sleep)
	{
		// printf("TEST = [%li]\n", timestamp - *timestamp_since_eaten);
		timestamp[0] = get_time();
		usleep(1000);
	}
	// usleep(v->values->time_to_sleep * 1000);
}

void	ft_think(t_thread *v, long first_timestamp, long timestamp_since_eaten)
{
	printf("%lims/%lims %i is thinking\n", get_time() - first_timestamp, get_time() - timestamp_since_eaten, v->id);
}

void	*philosophers(void *args)
{
	t_thread	*v;

	v = (t_thread*)args;
	printf("%i. ready!\n", v->id);
	v->ready = 1;
	while (*(v->start) == 0);
	if (!(v->id % 2))
		usleep(v->values->time_to_eat * 1000);
	v->first_timestamp = get_time();
	v->timestamp_since_eaten = v->first_timestamp;
	while (1)
	{
		ft_try_taking_forks(v, v->first_timestamp, v->timestamp_since_eaten);
		ft_eat(v, v->first_timestamp, &v->timestamp_since_eaten);
		ft_sleep(v, v->first_timestamp, v->timestamp_since_eaten);
		ft_think(v, v->first_timestamp, v->timestamp_since_eaten);
	}
	return (0);
}