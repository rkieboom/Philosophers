/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   join_threads.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 19:25:28 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:43:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	join_threads(pthread_t *pthread_id, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers + 1)
	{
		if (pthread_join(pthread_id[i], 0) != 0)
			return (ft_write_error("Joining thread failed!\n", 1));
		i++;
	}
	return (0);
}
