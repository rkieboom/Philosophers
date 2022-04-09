/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:07:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 18:40:24 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	init_philos(t_rules *rules, t_philo *ph, t_forks *temp)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		ph[i].id = i + 1;
		ph[i].forks = temp;
		ph[i].rules = rules;
		if (pthread_mutex_init(&ph[i].eat_count_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		if (pthread_mutex_init(&ph[i].stop_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		if (pthread_mutex_init(&ph[i].time.mutex, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		temp = temp->next;
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
		freeforks(v->forks);
		return (ft_write_error("Malloc failed!\n", 1));
	}
	if (init_philos(v->rules, ph, v->forks))
		return (1);
	v->ph = ph;
	return (0);
}
