/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:07:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/21 18:23:56 by rkieboom      ########   odam.nl         */
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

static	void	mutex_destroy_ph(t_list *v, int stop, int ret)
{
	int	i;

	i = 0;
	while (i < stop)
	{
		pthread_mutex_destroy(&v->ph[i].eat_count_m);
		pthread_mutex_destroy(&v->ph[i].stop_m);
		pthread_mutex_destroy(&v->ph[i].time.mutex);
	}
	if (ret == 2)
		pthread_mutex_destroy(&v->ph[i + 1].eat_count_m);
	else if (ret == 3)
	{
		pthread_mutex_destroy(&v->ph[i + 1].eat_count_m);
		pthread_mutex_destroy(&v->ph[i + 1].stop_m);
	}
}

static void	free_all_previous(t_list *v, int ret, int i)
{
	if (ret != 0)
		mutex_destroy_ph(v, i, ret);
	free_mutexes(v->forks_val, v->rules->number_of_philos);
	free(v->in_use);
	free(v->rules);
}

static int	init_philos(t_list *v, t_philo *ph, int *i)
{
	while (*i < v->rules->number_of_philos)
	{
		ph[*i].id = *i + 1;
		if (*i == 0)
		{
			ph[*i].left_val = &v->forks_val[v->rules->number_of_philos - 1];
			ph[*i].left_in_use = &v->in_use[v->rules->number_of_philos - 1];
		}
		else
		{
			ph[*i].left_val = &v->forks_val[*i - 1];
			ph[*i].left_in_use = &v->in_use[*i - 1];
		}
		ph[*i].right_in_use = &v->in_use[*i];
		ph[*i].right_val = &v->forks_val[*i];
		ph[*i].rules = v->rules;
		if (pthread_mutex_init(&ph[*i].eat_count_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 1));
		if (pthread_mutex_init(&ph[*i].stop_m, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 2));
		if (pthread_mutex_init(&ph[*i].time.mutex, 0) != 0)
			return (ft_write_error("Initializing mutex went wrong!\n", 3));
		(*i)++;
	}
	return (0);
}

int	setup_philos(t_list *v)
{
	int		i;
	int		temp;
	t_philo	*ph;

	i = 0;
	ph = ft_calloc(v->rules->number_of_philos, sizeof(t_philo));
	if (!ph)
	{
		free_all_previous(v, 0, 0);
		return (ft_write_error("Error, malloc failed!\n", 1));
	}
	temp = init_philos(v, ph, &i);
	if (temp)
	{
		free_all_previous(v, temp, i);
		return (1);
	}
	v->ph = ph;
	return (0);
}
