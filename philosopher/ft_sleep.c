/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sleep.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 15:17:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:29:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_thread *v)
{
	int	timestamp[2];

	timestamp[0] = get_time();
	timestamp[1] = get_time();
	printf("%lims %i is %ssleeping%s\n", \
	get_time() - v->first_timestamp, v->id, KRED, KWHT);
	while (timestamp[0] - timestamp[1] < v->values->time_to_sleep)
	{
		timestamp[0] = get_time();
		if (philo_died(v))
			break ;
		usleep(1000);
	}
}
