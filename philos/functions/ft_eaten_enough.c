/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_eaten_enough.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:57:08 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/14 03:50:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_eaten_enough(t_philo *v)
{
	pthread_mutex_lock(&v->eat_count_m);
	if (v->eat_count == v->rules->amount_of_times_to_eat)
	{
		pthread_mutex_unlock(&v->eat_count_m);
		return (1);
	}
	pthread_mutex_unlock(&v->eat_count_m);
	return (0);
}
