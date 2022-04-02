/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_threads.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 19:12:02 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:43:01 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int		create_threads(pthread_t *pthread_id, t_thread *th, t_args *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&pthread_id[i], 0, &philosophers, &th[i]) !=0)
			return (ft_write_error("Error, creating thread failed!\n", 1));
		i++;
	}
	if (pthread_create(&pthread_id[args->number_of_philosophers], 0, &monitoring_thread, th) != 0)
		return (ft_write_error("Error, creating thread failed!\n", 1));
	return (0);
}
