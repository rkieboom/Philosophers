/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:09:54 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/20 23:54:00 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_mutexes(pthread_mutex_t *free, int stop)
{
	int	i;

	i = 0;
	while (i < stop)
	{
		pthread_mutex_destroy(&free[i]);
		i++;
	}
}

int	init_forks(t_list *v)
{
	int	i;


	i = 0;
	v->forks = ft_calloc(v->rules->number_of_philos, sizeof(pthread_mutex_t));
	if (!v->forks)
		return (ft_write_error("Error, malloc failed!\n", 1));
	v->forks_val = ft_calloc(v->rules->number_of_philos, sizeof(pthread_mutex_t));
	if (!v->forks_val)
		return (ft_write_error("Error, malloc failed!\n", 1));
	v->in_use = ft_calloc(v->rules->number_of_philos, sizeof(int));
	if (!v->in_use)
		return (ft_write_error("Error, malloc failed!\n", 1));
	while (i < v->rules->number_of_philos)
	{
		if (pthread_mutex_init(&v->forks[i], 0) != 0)
		{
			free_mutexes(v->forks, i);
			return (ft_write_error("Error, initizalizing mutex went wrong!\n", 1));
		}
		i++;
	}
	i = 0;
	while (i < v->rules->number_of_philos)
	{
		if (pthread_mutex_init(&v->forks_val[i], 0) != 0)
		{
			free_mutexes(v->forks, v->rules->number_of_philos);
			free_mutexes(v->forks_val, i);
			return (ft_write_error("Error, initizalizing mutex went wrong!\n", 1));
		}
		i++;
	}
	//nog in_use freeyan
	return (0);
}
