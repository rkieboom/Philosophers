/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:07:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/20 23:55:31 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	init_philos(t_list *v, t_philo *ph)
{
	int	i;

	i = 0;
	while (i < v->rules->number_of_philos)
	{
		ph[i].id = i + 1;
		if (i == 0)
			ph[i].left = &v->forks[v->rules->number_of_philos - 1];
		else
			ph[i].left = &v->forks[i - 1];
		if (i == 0)
			ph[i].left_val = &v->forks_val[v->rules->number_of_philos - 1];
		else
			ph[i].left_val = &v->forks_val[i - 1];
		if (i == 0)
			ph[i].left_in_use = &v->in_use[v->rules->number_of_philos - 1];
		else
			ph[i].left_in_use = &v->in_use[i - 1];
			
		ph[i].right_in_use = &v->in_use[i];
		ph[i].right_val = &v->forks_val[i];
		ph[i].right = &v->forks[i];
		ph[i].rules = v->rules;
		if (pthread_mutex_init(&ph[i].eat_count_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		if (pthread_mutex_init(&ph[i].stop_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		if (pthread_mutex_init(&ph[i].time.mutex, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		i++;
	}
	return (0);
}

int		setup_philos(t_list *v)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = ft_calloc(v->rules->number_of_philos, sizeof(t_philo));
	if (!ph)
	{
		free(v->rules);
		return (ft_write_error("Malloc failed!\n", 1));
	}
	if (init_philos(v, ph))
		return (1);
	v->ph = ph;
	return (0);
}
