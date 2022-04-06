/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_forks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 19:09:43 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/06 21:16:01 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	*ft_free_forks(t_forks *forks, t_args *args)
{
	t_forks	*temp;

	temp = forks;
	while (temp)
	{
		forks = forks->right;
		pthread_mutex_destroy(&temp->fork);
		pthread_mutex_destroy(&temp->value);
		free(temp);
		temp = forks;
		if (forks && forks->last)
		{
			free(forks);
			break ;
		}
	}
	free(args);
	return (0);
}
