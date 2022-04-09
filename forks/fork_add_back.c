/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_add_back.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:22:43 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/08 18:34:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

int		fork_add_back(t_forks *forks, int last)
{
	t_forks *temp;

	temp = fork_last(forks);
	temp->next = ft_calloc(1, sizeof(t_forks));
	if (!temp->next)
	{
		temp = forks;
		while (forks)
		{
			free(temp);
			temp = temp->next;
		}
		return (ft_write_error("Malloc failed!\n", 1));
	}
	if (last == 1)
	{
		temp->next->last = 1;
		temp->next->next = forks;
	}
	return (0);
}
