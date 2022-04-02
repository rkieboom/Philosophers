/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_died.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 16:30:30 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 16:32:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_thread *v)
{
	if (*(v->start) == 0)
		return (1);
	return (0);
}
