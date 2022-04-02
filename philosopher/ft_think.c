/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_think.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 15:17:07 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 15:55:35 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_thread *v)
{
	printf("%lims %i is thinking\n", get_time() - v->first_timestamp, v->id);
}
