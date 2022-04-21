/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_and_start_threads.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:21:21 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:37:16 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../philos/philo.h"
#include <pthread.h>

static void	destroy_all_mutexes(t_list *v)
{
	int	i;

	i = 0;
	while (i < v->rules->number_of_philos)
	{
		pthread_mutex_destroy(&v->forks_val[i]);
		pthread_mutex_destroy(&v->ph[i].eat_count_m);
		pthread_mutex_destroy(&v->ph[i].stop_m);
		pthread_mutex_destroy(&v->ph[i].time.mutex);
		i++;
	}
}

static void	free_all_previous(t_list *v)
{
	destroy_all_mutexes(v);
	free(v->rules);
	free(v->ph);
	free(v->in_use);
	free(v->forks_val);
}

int	join_threads(t_list *v, pthread_t *threads, int number_of_philos)
{
	int	i;

	i = 0;
	while (i < number_of_philos + 1)
	{
		if (pthread_join(threads[i], 0) != 0)
		{
			free_all_previous(v);
			free(threads);
			return (ft_write_error("Error, joining threads failed!\n", 1));
		}
		i++;
	}
	free(threads);
	return (0);
}

int	create_threads(t_list *v, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < v->rules->number_of_philos)
	{
		if (pthread_create(&threads[i], 0, &philo, &v->ph[i]) != 0)
		{
			free_all_previous(v);
			free(threads);
			return (ft_write_error("Error, creating thread failed!\n", 1));
		}
		i++;
	}
	if (pthread_create(&threads[v->rules->number_of_philos], \
	0, &monitoring_thread, v->ph) != 0)
		return (ft_write_error("Error, creating thread failed!\n", 1));
	return (0);
}

int	create_and_start_threads(t_list *v)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = ft_calloc(v->rules->number_of_philos + 1, sizeof(pthread_t));
	if (!threads)
	{
		free_all_previous(v);
		return (ft_write_error("Malloc failed!\n", 1));
	}
	if (create_threads(v, threads))
		return (1);
	if (join_threads(v, threads, v->rules->number_of_philos))
		return (1);
	return (0);
}
