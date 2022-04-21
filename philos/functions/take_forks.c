/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   take_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 17:23:55 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	take_right_fork(t_philo *v)
{
	while (1)
	{
		pthread_mutex_lock(v->right_val);
		if (*v->right_in_use == 0)
		{
			*v->right_in_use = 1;
			pthread_mutex_unlock(v->right_val);
			printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
			return (0);
		}
		pthread_mutex_unlock(v->right_val);
		usleep(100);
		if (ft_stop(v))
			return (1);
	}
}

static int	take_left_fork(t_philo *v)
{
	while (1)
	{
		pthread_mutex_lock(v->left_val);
		if (*v->left_in_use == 0)
		{
			*v->left_in_use = 1;
			pthread_mutex_unlock(v->left_val);
			printf("%lims %i has taken %sfork%s\n", get_time() - v->time.first_timestamp, v->id, KRED, KWHT);
			return (0);
		}
		pthread_mutex_unlock(v->left_val);
		usleep(100);
		if (ft_stop(v))
			return (1);
	}
}


int			ft_take_forks(t_philo *v)
{
	if (take_right_fork(v))
		return (1);
	if (take_left_fork(v))
		return (1);
	return (0);
}
