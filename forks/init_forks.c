/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/02 18:45:23 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 19:41:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_forks	*init_forks(t_forks *forks, t_args *args, int i)
{
	t_forks	*temp;

	while (i < args->number_of_philosophers)
	{
		if (i == 0)
		{
			forks = fork_create();
			if (!forks)
				return (0);
		}
		else
		{
			temp = fork_create();
			if (!temp)
			{
				ft_free_forks(forks, args);
				return (0);
			}
			if (i + 1 == args->number_of_philosophers)
				fork_add_back_last(&forks, temp);
			else
				fork_add_back(&forks, temp);
		}
		i++;
	}
	return (forks);
}
