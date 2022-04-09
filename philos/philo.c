/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 23:56:30 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 13:58:06 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *args)
{
	t_philo *v;

	v = (t_philo *)args;
	printf("%i. ready!\n", v->id);
	return (0);
}
