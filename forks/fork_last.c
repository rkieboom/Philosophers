/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_last.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 17:23:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/09 00:06:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

t_forks	*fork_last(t_forks *fork)
{
	t_forks	*temp;

	temp = fork;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
