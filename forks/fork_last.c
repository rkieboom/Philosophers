/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_last.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/06 15:14:57 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/02 13:12:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"

t_forks	*fork_last(t_forks *lst)
{
	if (!lst)
		return (NULL);
	while (lst->right != NULL)
	{
		if (lst->last == 1)
			return (lst);
		lst = lst->right;
	}
	return (lst);
}
