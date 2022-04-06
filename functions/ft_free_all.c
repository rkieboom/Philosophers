/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_all.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 19:15:16 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:19:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_free_all(t_thread *th, pthread_t *pthread_id)
{
	// free(th->start);
	ft_free_forks(th->forks, th->values);
	free(pthread_id);
	free(th);
	return (1);
}
