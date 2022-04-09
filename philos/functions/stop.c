/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stop.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:49:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 14:55:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_stop(t_philo *v)
{
	pthread_mutex_lock(&v->stop_m);
	if (v->stop == 1)
	{
		pthread_mutex_unlock(&v->stop_m);
		return (1);
	}
	pthread_mutex_unlock(&v->stop_m);
	return (0);
}
