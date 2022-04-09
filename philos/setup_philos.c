/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_philos.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/09 01:07:31 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 14:14:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		setup_philos(t_list *v)
{
	int		i;
	t_philo	*ph;
	t_forks	*temp;

	i = 0;
	temp = v->forks;
	ph = ft_calloc(v->rules->number_of_philos, sizeof(t_philo));
	if (!ph)
	{
		free(v->rules);
		freeforks(v->forks);
		return (ft_write_error("Malloc failed!\n", 1));
	}
	while (i < v->rules->number_of_philos)
	{
		ph[i].id = i + 1;
		ph[i].forks = temp;
		temp = temp->next;
		i++;
	}
	v->ph = ph;
	return (0);
}
