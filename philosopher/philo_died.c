/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_died.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 16:30:30 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:29:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_thread *v)
{
	pthread_mutex_lock(&v->mutex);
	if (v->died == 1)
	{
		pthread_mutex_unlock(&v->mutex);
		return (1);
	}
	pthread_mutex_unlock(&v->mutex);
	return (0);
}
