/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:09:54 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 17:25:20 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_mutexes(pthread_mutex_t *free_v, int stop)
{
	int	i;

	i = 0;
	while (i < stop)
	{
		pthread_mutex_destroy(&free_v[i]);
		i++;
	}
	free(free_v);
}

int	init_forks(t_list *v)
{
	int	i;


	i = 0;
	v->forks_val = ft_calloc(v->rules->number_of_philos, sizeof(pthread_mutex_t));
	if (!v->forks_val)
		return (ft_write_error("Error, malloc failed!\n", 1));
	v->in_use = ft_calloc(v->rules->number_of_philos, sizeof(int));
	if (!v->in_use)
		return (ft_write_error("Error, malloc failed!\n", 1));
	while (i < v->rules->number_of_philos)
	{
		if (pthread_mutex_init(&v->forks_val[i], 0) != 0)
		{
			free_mutexes(v->forks_val, i);
			free(v->in_use);
			return (ft_write_error("Error, initizalizing mutex went wrong!\n", 1));
		}
		i++;
	}
	return (0);
}
