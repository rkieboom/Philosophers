/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:22:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	put_forks_back(t_philo *v)
{
	pthread_mutex_lock(v->right_val);
	pthread_mutex_lock(v->left_val);
	*v->left_in_use = 0;
	*v->right_in_use = 0;
	pthread_mutex_unlock(v->right_val);
	pthread_mutex_unlock(v->left_val);
}

void	ft_sleep(t_philo *v)
{
	int	timestamp[2];

	timestamp[0] = get_time();
	timestamp[1] = get_time();
	pthread_mutex_lock(&v->stop_m);
	if (v->stop == 1)
	{
		pthread_mutex_unlock(&v->stop_m);
		return ;
	}
	printf("%lims %i is %ssleeping%s\n", \
	get_time() - v->time.first_timestamp, v->id, KBLU, KWHT);
	pthread_mutex_unlock(&v->stop_m);
	put_forks_back(v);
	while (timestamp[0] - timestamp[1] < v->rules->time_to_sleep)
	{
		timestamp[0] = get_time();
		if (ft_stop(v))
			break ;
		usleep(1000);
	}
}
