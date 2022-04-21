/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eaten_enough.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:57:08 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 02:50:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_eaten_enough(t_philo *v)
{
	pthread_mutex_lock(&v->eat_count_m);
	if (v->eat_count == v->rules->amount_of_times_to_eat)
	{
		pthread_mutex_unlock(&v->eat_count_m);
		pthread_mutex_lock(v->right_val);
		*v->right_in_use = 0;
		pthread_mutex_unlock(v->right_val);
		pthread_mutex_lock(v->left_val);
		*v->left_in_use = 0;
		pthread_mutex_unlock(v->left_val);
		return (1);
	}
	pthread_mutex_unlock(&v->eat_count_m);
	return (0);
}
