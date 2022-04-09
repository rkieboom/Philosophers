/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks_create.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:18:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/08 17:22:09 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

t_forks	*fork_create()
{
	t_forks *temp;

	temp = ft_calloc(1, sizeof(t_forks));
	if (!temp)
	{
		ft_write_error("Malloc failed!\n", 1);
		return (0);
	}
	return (temp);
}
