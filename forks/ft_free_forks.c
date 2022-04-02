/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_forks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 19:09:43 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 20:02:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_free_forks(t_forks *forks, t_args *args)
{
	t_forks	*temp;

	temp = forks;
	while (temp)
	{
		forks = forks->right;
		pthread_mutex_destroy(&temp->mutex);
		free(temp);
		temp = forks;
		if (forks && forks->last)
		{
			free(forks);
			break ;
		}
	}
	free(args);
}
