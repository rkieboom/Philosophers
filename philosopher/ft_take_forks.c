/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_take_forks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 15:17:02 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 21:05:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	in_hungry_state2(t_thread *v, long first_timestamp)
{
	if (v->forks->in_use && !v->forks->right->in_use)
	{
		pthread_mutex_lock(&v->forks->right->mutex);
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->mutex);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
	}
	else if (!v->forks->in_use && v->forks->right->in_use)
	{
		pthread_mutex_lock(&v->forks->right->mutex);
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->mutex);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
	}
	else
		return (0);
	return (1);
}

static int	in_hungry_state(t_thread *v, long first_timestamp)
{
	if (in_hungry_state2(v, first_timestamp))
		return (0);
	else if (v->forks->in_use && v->forks->right->in_use)
		return (1);
	else
	{
		pthread_mutex_lock(&v->forks->right->mutex);
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->mutex);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
	}
	return (0);
}

static void	lock_forks(t_thread *v, long first_timestamp)
{
	if (v->id % 2)
	{
		pthread_mutex_lock(&v->forks->mutex);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->right->mutex);
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
	}
	else
	{
		pthread_mutex_lock(&v->forks->right->mutex);
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->mutex);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
	}
}

void	ft_take_forks(t_thread *v)
{
	while (1)
	{
		if (((v->values->time_to_die - v->values->time_to_sleep) / 2) \
		< v->timestamp_since_eaten)
			v->hungry = 1;
		if ((v->forks->in_use == 0 && v->forks->right->in_use == 0) \
		|| v->hungry == 1)
		{
			if (v->values->number_of_philosophers % 2 \
			&& v->id % 2 && v->hungry == 0)
				usleep(500);
			if (v->hungry == 1)
			{
				if (in_hungry_state(v, v->first_timestamp))
					continue ;
			}
			else
				lock_forks(v, v->first_timestamp);
			v->forks->in_use = 1;
			v->forks->right->in_use = 1;
			v->hungry = 0;
			break ;
		}
	}
}
