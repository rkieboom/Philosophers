/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_take_forks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 15:17:02 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/08 00:38:54 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	in_hungry_state2(t_thread *v, long first_timestamp)
{
	if (v->forks->in_use && !v->forks->right->in_use)
	{
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->right->fork);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->fork);
	}
	else if (!v->forks->in_use && v->forks->right->in_use)
	{
		printf("%lims %i has taken %sright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->right->fork);
		printf("%lims %i has taken %sleft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, KWHT);
		pthread_mutex_lock(&v->forks->fork);
	}
	else
		return (0);
	return (1);
}

static int	in_hungry_state(t_thread *v, long first_timestamp)
{
	// printf("%li %i here1\n", get_time() - v->first_timestamp, v->id);
	pthread_mutex_lock(&v->forks->value);
	// printf("%li %i here2\n", get_time() - v->first_timestamp ,v->id);
	pthread_mutex_lock(&v->forks->right->value);
	// printf("%li %i here3\n", get_time() - v->first_timestamp ,v->id);
	// printf("%i lfork=%i rfork=%i\n", v->id, v->forks->in_use, v->forks->right->in_use);
	fflush(0);
	if (in_hungry_state2(v, first_timestamp))
	{
		pthread_mutex_unlock(&v->forks->value);
		pthread_mutex_unlock(&v->forks->right->value);
		printf("%i returned 1\n", v->id);
		return (1);
	}
	else if (v->forks->in_use && v->forks->right->in_use)
	{
		pthread_mutex_unlock(&v->forks->value);
		pthread_mutex_unlock(&v->forks->right->value);
		return (0);
	}
	else
	{
		printf("%lims %i has taken %s%iright fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->right->id ,KWHT);
		pthread_mutex_lock(&v->forks->right->fork);
		printf("%lims %i has taken %s%ileft fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->id ,KWHT);
		pthread_mutex_lock(&v->forks->fork);
		printf("%lims %i inhereeeeeeee\n", get_time() - v->first_timestamp, v->id);
	}
	printf("%i returned 0\n", v->id);
	pthread_mutex_unlock(&v->forks->value);
	pthread_mutex_unlock(&v->forks->right->value);
	return (1);
}

static void	lock_forks(t_thread *v, long first_timestamp)
{
	if (v->id % 2)
	{
		printf("%lims %i has taken %s%i. left fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->id , KWHT);
		pthread_mutex_lock(&v->forks->fork);
		printf("%lims %i has taken %s%i. right fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->right->id ,KWHT);
		pthread_mutex_lock(&v->forks->right->fork);
	}
	else
	{
		printf("%lims %i has taken %s%i. right fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->right->id ,KWHT);
		pthread_mutex_lock(&v->forks->right->fork);
		printf("%lims %i has taken %s%i. left fork%s\n", get_time() \
		- first_timestamp, v->id, KBLU, v->forks->id , KWHT);
		pthread_mutex_lock(&v->forks->fork);
	}
}

void	ft_old_take_forks(t_thread *v)
{
	while (1)
	{
		if (((v->values->time_to_die - v->values->time_to_sleep) / 2) \
		< v->timestamp_since_eaten)
			v->hungry = 1;
		// pthread_mutex_lock(&v->mutex);
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


void	ft_take_forks(t_thread *v)
{
	while (1)
	{
		if (((v->values->time_to_die - v->values->time_to_sleep) / 2) \
		< v->timestamp_since_eaten)
			v->hungry = 1;
		if (v->hungry == 1)
		{
			printf("%lims %i is hungry\n", get_time() - v->first_timestamp ,v->id);
			fflush(0);
			v->hungry = 0;
			if (in_hungry_state(v, v->first_timestamp))
				return ;
		}
		else
		{
			pthread_mutex_lock(&v->forks->value);
			pthread_mutex_lock(&v->forks->right->value);
			if (v->forks->in_use == 0 && v->forks->right->in_use == 0)
			{
				if (v->values->number_of_philosophers % 2 \
				&& v->id % 2 && v->hungry == 0)
				usleep(500);
				lock_forks(v, v->first_timestamp);
				v->forks->in_use = 1;
				v->forks->right->in_use = 1;
				pthread_mutex_unlock(&v->forks->value);
				pthread_mutex_unlock(&v->forks->right->value);
				return ;
			}
			pthread_mutex_unlock(&v->forks->value);
			pthread_mutex_unlock(&v->forks->right->value);
		}
	}
}
