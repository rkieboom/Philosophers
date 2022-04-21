/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 18:15:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:39:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../philos/philo.h"

static int	check_to_start(t_philo *v, int i)
{
	if (i == v->rules->number_of_philos)
	{
		i = 0;
		while (i < v->rules->number_of_philos)
		{
			pthread_mutex_lock(&v[i].stop_m);
			v[i].start = 2;
			pthread_mutex_unlock(&v[i].stop_m);
			i++;
		}
		return (1);
	}
	return (0);
}

void	start_philos(t_philo *v)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < v->rules->number_of_philos)
		{
			pthread_mutex_lock(&v[i].stop_m);
			if (v[i].start != 1)
			{
				pthread_mutex_unlock(&v[i].stop_m);
				break ;
			}
			pthread_mutex_unlock(&v[i].stop_m);
			i++;
		}
		if (check_to_start(v, i))
			return ;
	}
}
