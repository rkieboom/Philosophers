/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   think.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 14:45:47 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/14 03:55:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_think(t_philo *v)
{
	pthread_mutex_lock(&v->stop_m);
	if (v->stop == 1)
	{
		pthread_mutex_unlock(&v->stop_m);
		return ;
	}
	printf("%lims %i is thinking\n", \
	get_time() - v->time.first_timestamp, v->id);
	pthread_mutex_unlock(&v->stop_m);
}
