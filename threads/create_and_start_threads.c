/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_and_start_threads.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:21:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/20 23:27:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../philos/philo.h"
#include <pthread.h>

int	join_threads(pthread_t *threads, int number_of_philos)
{
	int	i;

	i = 0;
	while (i < number_of_philos + 1)
	{
		if (pthread_join(threads[i], 0) != 0)
			ft_write_error("Error, joining threads failed!\n", 1);
		i++;
	}
	free(threads);
	return (0);
}

int	create_and_start_threads(t_list *v)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = ft_calloc(v->rules->number_of_philos + 1, sizeof(pthread_t));
	if (!threads)
		return (ft_write_error("Malloc failed!\n", 1));
	while (i < v->rules->number_of_philos)
	{
		if (pthread_create(&threads[i], 0, &philo, &v->ph[i]) != 0)
			return (ft_write_error("Error, creating thread failed!\n", 1));
		i++;
	}
	if (pthread_create(&threads[v->rules->number_of_philos], 0, &monitoring_thread, v->ph) != 0)
		return (ft_write_error("Error, creating thread failed!\n", 1));
	if (join_threads(threads, v->rules->number_of_philos))
	{
		free(v->rules);
		free(threads);
		return (1);
	}
	return (0);
}
