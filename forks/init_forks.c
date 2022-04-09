/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_forks.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:09:54 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 14:43:16 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

void	freeforks(t_forks *forks)
{
	t_forks	*temp;

	if (!forks)
		return ;
	temp = forks->next;
	if (!temp)
	{
		free(forks);
		return ;
	}
	while (forks)
	{
		if (forks->last == 1)
		{
			free(forks);
			return ;
		}
		free(forks);
		forks = temp;
		temp = temp->next;
	}
}

int	init_forks(t_list *v, int i)
{
	t_forks	*fork;

	while (i < v->rules->number_of_philos)
	{
		if (i == 0)
		{
			fork = fork_create();
			if (!fork)
			{
				free(v->rules);
				return (ft_write_error("Malloc failed!\n", 1));
			}
			fork->id = 1;
		}
		else
			if (fork_add_back(fork, i + 1 == v->rules->number_of_philos))
			{
				free(v->rules);
				freeforks(fork);
				return (ft_write_error("Malloc failed!\n", 1));
			}
		i++;
	}
	v->forks = fork;
	return (0);
}